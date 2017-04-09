#include <comp/ir/build_ir.h>

#include <iostream>

#include <comp/ir/builtins.h>
#include <comp/ir/control_flow_graph.h>
#include <comp/ir/op.h>
#include <comp/utils/exceptions.h>
#include <comp/utils.h>

namespace comp {
namespace ir {
std::unique_ptr<Program> BuildProgramIR(const ast::Program &program_node) {
  std::unique_ptr<Program> program = Program::Create();
  RootContext context = CreateRootContextWithBuiltIns();
  for (auto declaration : program_node.body) {
    switch (declaration->node_type) {
      case ast::Node::Type::Function: {
        std::shared_ptr<ast::Function>
          e = std::static_pointer_cast<ast::Function>(declaration);
        std::shared_ptr<const FunctionSymbol> function = BuildFunctionIR(
          *e, context);
        if (function != nullptr) {
          program->AddSymbol(function);
        }
        break;
      }
      case ast::Node::Type::VariableDeclaration: {
        throw std::domain_error("Not implemented: global variable declarations");
      }
      default: {
        throw UnexpectedNodeTypeError(*declaration);
      }
    }
  }

  return program;
}

std::shared_ptr<FunctionSymbol> BuildFunctionIR(
  const ast::Function &node, Context &context
) {
  // Create the IR of the function's parameters
  std::vector<std::shared_ptr<const Variable>> parameters;
  for (auto parameter : node.parameters) {
    std::shared_ptr<const DataType> data_type = ResolveParameterType(*parameter, context);
    std::string name = ResolveParameterName(*parameter);
    parameters.push_back(Variable::Create(data_type, parameter));
  }

  // Create the IR of the function's return type
  std::shared_ptr<const DataType> return_type = ResolveDataTypeType(*node.return_type, context);

  // Add declaration to context, if it hasn't already been done
  std::shared_ptr<FunctionSymbol> function;
  try {
    function = context.ResolveFunction(node.identifier->name);
  } catch (std::runtime_error &) {
    // Register the function's symbol (without a body initially)
    function = FunctionSymbol::Create(
      node.identifier->name, parameters, return_type);
    context.RegisterFunction(node.identifier->name, function);
    if (node.body == nullptr) {
      return nullptr;
    }
  }

  // Ensure this function is not being declared twice or defined twice
  if (node.body == nullptr) {
    throw FunctionAlreadyDeclaredError(node);
  }
  if (function->GetBody() != nullptr) {
    throw FunctionAlreadyDefinedError(node);
  }

  // Check that the function signatures match
  if (parameters.size() != function->GetParameters().size()) {
    throw FunctionParameterListDoesNotMatchError(node);
  }
  if (return_type != function->GetReturnType()) {
    throw FunctionReturnTypeDoesNotMatchError(node);
  }
  for (size_t i = 0; i < parameters.size(); i++) {
    if (parameters[i]->GetDataType() !=
      function->GetParameters()[i]->GetDataType()) {
      throw FunctionParameterTypeDoesNotMatchError(
        *std::static_pointer_cast<const ast::Parameter>(
          parameters[i]->GetAstNode()));
    }
  }
  // Create the child context
  VariablesTable variables_table;
  std::vector<std::shared_ptr<const Variable>> variables_set;
  for (size_t i = 0; i < node.parameters.size(); i++) {
    std::string parameter_name = ResolveParameterName(*node.parameters[i]);
    if (parameter_name != "") {
      variables_table[parameter_name] = parameters[i];
    }
    variables_set.push_back(parameters[i]);
  }
  ChildContext function_context(context, SymbolTable({}, variables_table, {}), variables_set);

  // Generate the function's control flow graph
  std::shared_ptr<ControlFlowGraph> cfg = ControlFlowGraph::Create();
  std::shared_ptr<BasicBlock> current_block = cfg->GetSource();
  BuildBlockStatementIR(*node.body, function_context, cfg, current_block);
  if (current_block->GetType() == BasicBlock::Type::Incomplete) {
    current_block->SetReturn(nullptr);
  }
  function->SetBody(cfg);
  function->SetLocalVariables(function_context.GetVariables());

  return function;
}

std::shared_ptr<const DataType> ResolveDataTypeType(const ast::DataType &data_type, const Context &context) {
  switch (data_type.node_type) {
    case ast::Node::Type::ArrayDataType: {
      const ast::ArrayDataType &arrayDataType = static_cast<const ast::ArrayDataType &>(data_type);
      if (arrayDataType.size != nullptr) {
        size_t size;
        switch (arrayDataType.size->node_type) {
          case ast::Node::Type::Int64Literal:
            size = std::static_pointer_cast<ast::Int64Literal>(arrayDataType.size)->value;
            break;
          case ast::Node::Type::Uint8Literal:
            size = std::static_pointer_cast<ast::Uint8Literal>(arrayDataType.size)->value;
            break;
          default:
            // Currently, we only support literals to specify array size
            throw ArrayLengthNotLiteralError(arrayDataType);
        }
        return ArrayDataType::Create(ResolveDataTypeType(*arrayDataType.item_type, context), size);
      } else {
        return PointerDataType::Create(ResolveDataTypeType(*arrayDataType.item_type, context));
      }
    }
    case ast::Node::Type::IdentifierDataType: {
      const ast::IdentifierDataType &identifierDeclarator = static_cast<const ast::IdentifierDataType &>(data_type);
      return context.ResolveDataType(identifierDeclarator.identifier->name);
    }
    default: {
      throw UnexpectedNodeTypeError(data_type);
    }
  }
}

std::shared_ptr<const DataType> ResolveDeclaratorType(const std::shared_ptr<const DataType> base_type,
                                                      const ast::Declarator &declarator) {
  switch (declarator.node_type) {
    case ast::Node::Type::ArrayDeclarator: {
      const ast::ArrayDeclarator &arrayDeclarator = static_cast<const ast::ArrayDeclarator &>(declarator);
      std::shared_ptr<const DataType> item_type = ResolveDeclaratorType(base_type, *arrayDeclarator.declarator);
      if (arrayDeclarator.size == nullptr) {
        return PointerDataType::Create(item_type);
      } else {
        if (arrayDeclarator.size->node_type != ast::Node::Type::Int64Literal) {
          throw comp::CannotSpecifySizeError(declarator.location);
        }
        int64_t array_size = std::static_pointer_cast<ast::Int64Literal>(arrayDeclarator.size)->value;
        return ArrayDataType::Create(item_type, size_t(array_size));
      }
    }
    case ast::Node::Type::IdentifierDeclarator: {
      return base_type;
    }
    default: {
      throw UnexpectedNodeTypeError(declarator);
    }
  }
}

std::shared_ptr<const DataType> ResolveParameterType(const ast::Parameter &parameter, const Context &context) {
  switch (parameter.node_type) {
    case ast::Node::Type::NamedParameter: {
      const ast::NamedParameter &namedParameter = static_cast<const ast::NamedParameter &>(parameter);
      return ResolveDeclaratorType(ResolveDataTypeType(*namedParameter.data_type, context), *namedParameter.declarator);
    }
    case ast::Node::Type::AnonymousParameter: {
      const ast::AnonymousParameter &anonymousParameter = static_cast<const ast::AnonymousParameter &>(parameter);
      return ResolveDataTypeType(*anonymousParameter.data_type, context);
    }
    default: {
      throw UnexpectedNodeTypeError(parameter);
    }
  }
}

std::string ResolveDeclaratorName(const ast::Declarator &declarator) {
  switch (declarator.node_type) {
    case ast::Node::Type::ArrayDeclarator: {
      return ResolveDeclaratorName(*static_cast<const ast::ArrayDeclarator &>(declarator).declarator);
    }
    case ast::Node::Type::IdentifierDeclarator: {
      return static_cast<const ast::IdentifierDeclarator &>(declarator).identifier->name;
    }
    default: {
      throw UnexpectedNodeTypeError(declarator);
    }
  }
}

std::string ResolveParameterName(const ast::Parameter &parameter) {
  switch (parameter.node_type) {
    case ast::Node::Type::NamedParameter: {
      const ast::NamedParameter &namedParameter = static_cast<const ast::NamedParameter &>(parameter);
      return ResolveDeclaratorName(*namedParameter.declarator);
    }
    case ast::Node::Type::AnonymousParameter: {
      return "";
    }
    default: {
      throw UnexpectedNodeTypeError(parameter);
    }
  }
}

void BuildStatementIR(
  const ast::Statement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  switch (node.node_type) {
    case ast::Node::Type::BlockStatement: {
      BuildBlockStatementIR(
        static_cast<const ast::BlockStatement &>(node),
        context,
        cfg,
        current_block);
      break;
    }
    case ast::Node::Type::ExpressionStatement: {
      BuildExpressionStatementIR(
        static_cast<const ast::ExpressionStatement &>(node),
        context,
        cfg,
        current_block);
      break;
    }
    case ast::Node::Type::ForStatement: {
      BuildForStatementIR(
        static_cast<const ast::ForStatement &>(node),
        context,
        cfg,
        current_block
      );
      break;
    }
    case ast::Node::Type::IfStatement: {
      BuildIfStatementIR(
        static_cast<const ast::IfStatement &>(node),
        context,
        cfg,
        current_block
      );
      break;
    }
    case ast::Node::Type::NullStatement: {
      BuildNullStatementIR(
        static_cast<const ast::NullStatement &>(node),
        context,
        cfg,
        current_block
      );
      break;
    }
    case ast::Node::Type::ReturnStatement: {
      BuildReturnStatementIR(
        static_cast<const ast::ReturnStatement &>(node),
        context,
        cfg,
        current_block
      );
      break;
    }
    case ast::Node::Type::VariableDeclaration: {
      BuildVariableDeclarationIR(
        static_cast<const ast::VariableDeclaration &>(node),
        context,
        cfg,
        current_block);
      break;
    }
    case ast::Node::Type::WhileStatement: {
      BuildWhileStatementIR(
        static_cast<const ast::WhileStatement &>(node),
        context,
        cfg,
        current_block
      );
      break;
    }
    default: {
      throw UnexpectedNodeTypeError(node);
    }
  }
}

void BuildBlockStatementIR(
  const ast::BlockStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  std::unique_ptr<ChildContext> childContext = context.Fork();
  for (auto statement : node.body) {
    if (current_block->GetType() != BasicBlock::Type::Incomplete) {
      std::cerr << "Warning: Found some dead code...\n";
      break;
    }
    BuildStatementIR(*statement, *childContext, cfg, current_block);
  }
  context.Join(std::move(childContext));
}

void BuildExpressionStatementIR(
  const ast::ExpressionStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  BuildRExpressionIR(node.expression, context, cfg, current_block);
}

void BuildVariableDeclarationIR(
  const ast::VariableDeclaration &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  std::shared_ptr<const ir::DataType> basic_type = ResolveDataTypeType(*node.data_type, context);
  for (auto variable_declarator: node.declarators) {
    std::string variable_name = ResolveDeclaratorName(*variable_declarator->declarator);
    std::shared_ptr<const ir::DataType>
      variable_type = ResolveDeclaratorType(basic_type, *variable_declarator->declarator);
    std::shared_ptr<const Variable> variable = Variable::Create(variable_type);
    context.RegisterVariable(variable_name, variable);
    if (variable_declarator->initial_value != nullptr) {
      std::shared_ptr<Operand>
        initial_value = BuildRExpressionIR(variable_declarator->initial_value, context, cfg, current_block);
      current_block->Push(CopyOp::Create(
        VariableOperand::Create(variable),
        initial_value
      ));
    }
  }
}

std::shared_ptr<Operand> BuildRExpressionIR(
  const std::shared_ptr<ast::RExpression> node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  switch (node->node_type) {
    case ast::Node::Type::AssignmentExpression: {
      return BuildAssignmentExpressionIR(
        std::dynamic_pointer_cast<ast::AssignmentExpression>(node),
        context,
        cfg,
        current_block);
    }
    case ast::Node::Type::BinaryExpression: {
      return BuildBinaryExpressionIR(
        std::dynamic_pointer_cast<ast::BinaryExpression>(node),
        context,
        cfg,
        current_block);
    }
    case ast::Node::Type::CallExpression: {
      return BuildCallExpressionIR(
        std::dynamic_pointer_cast<ast::CallExpression>(node),
        context,
        cfg,
        current_block);
    }
    case ast::Node::Type::ConditionalExpression: {
      return BuildConditionalExpressionIR(
        std::dynamic_pointer_cast<ast::ConditionalExpression>(node),
        context,
        cfg,
        current_block);
    }
    case ast::Node::Type::Identifier: {
      return BuildIdentifierIR(
        std::dynamic_pointer_cast<ast::Identifier>(node),
        context);
    }
    case ast::Node::Type::Int64Literal: {
      return BuildInt64LiteralIR(
        std::dynamic_pointer_cast<ast::Int64Literal>(node),
        context);
    }
    case ast::Node::Type::LogicalExpression: {
      return BuildLogicalExpressionIR(
        std::dynamic_pointer_cast<ast::LogicalExpression>(node),
        context,
        cfg,
        current_block);
    }
    case ast::Node::Type::SubscriptExpression: {
      return BuildSubscriptExpressionIR(
        std::dynamic_pointer_cast<ast::SubscriptExpression>(node),
        context,
        cfg,
        current_block);
    }
    case ast::Node::Type::Uint8Literal: {
      return BuildUint8LiteralIR(
        std::dynamic_pointer_cast<ast::Uint8Literal>(node),
        context);
    }
    case ast::Node::Type::UnaryExpression: {
      return BuildUnaryExpressionIR(
        std::dynamic_pointer_cast<ast::UnaryExpression>(node),
        context,
        cfg,
        current_block);
    }
    default: {
      throw UnexpectedNodeTypeError(*node);
    }
  }
}

std::shared_ptr<WritableOperand> BuildLExpressionIR(
  const std::shared_ptr<ast::LExpression> node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  switch (node->node_type) {
    case ast::Node::Type::Identifier: {
      return BuildIdentifierIR(
        std::dynamic_pointer_cast<ast::Identifier>(node),
        context);
    }
    case ast::Node::Type::SubscriptExpression: {
      return BuildSubscriptExpressionIR(
        std::dynamic_pointer_cast<ast::SubscriptExpression>(node),
        context,
        cfg,
        current_block);
    }
    default: {
      throw std::domain_error(
        "Unexpected value for `node->node_type` in `BuildLExpressionIR`");
    }
  }
}

std::shared_ptr<Operand> BuildAssignmentExpressionIR(
  const std::shared_ptr<ast::AssignmentExpression> node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  const std::shared_ptr<WritableOperand> left = BuildLExpressionIR(node->left, context, cfg, current_block);
  std::shared_ptr<Operand> right = BuildRExpressionIR(node->right, context, cfg, current_block);
  const std::shared_ptr<const DataType> left_type = GetOperandType(*left);
  const std::shared_ptr<const DataType> right_type = GetOperandType(*right);

  if (!right_type->IsCastableTo(*left_type)) {
    throw std::runtime_error("Unable to cast type of right operand to type of left operand in `BuildAssignmentExpressionIR`");
  } else if(*right_type != *left_type) {
    const std::shared_ptr<const DataType> casted_right_type = left_type->GetCommonType(*right_type);
    const std::shared_ptr<const Variable> casted_right_var = context.CreateVariable(casted_right_type);
    const std::shared_ptr<VariableOperand> casted_right = VariableOperand::Create(casted_right_var);
    current_block->Push(CastOp::Create(casted_right, right));
    right = casted_right;
  }

  switch (node->op) {
    case ast::AssignmentOperator::Addition: {
      current_block->Push(BinOp::Create(left, BinOp::BinaryOperator::Addition, left, right));
      break;
    }
    case ast::AssignmentOperator::BitwiseAnd: {
      current_block->Push(BinOp::Create(left, BinOp::BinaryOperator::BitwiseAnd, left, right));
      break;
    }
    case ast::AssignmentOperator::BitwiseOr: {
      current_block->Push(BinOp::Create(left, BinOp::BinaryOperator::BitwiseOr, left, right));
      break;
    }
    case ast::AssignmentOperator::BitwiseXor: {
      current_block->Push(BinOp::Create(left, BinOp::BinaryOperator::BitwiseXor, left, right));
      break;
    }
    case ast::AssignmentOperator::Division: {
      current_block->Push(BinOp::Create(left, BinOp::BinaryOperator::Division, left, right));
      break;
    };
    case ast::AssignmentOperator::LeftShift: {
      current_block->Push(BinOp::Create(left, BinOp::BinaryOperator::LeftShift, left, right));
      break;
    };
    case ast::AssignmentOperator::Multiplication: {
      current_block->Push(BinOp::Create(left, BinOp::BinaryOperator::Multiplication, left, right));
      break;
    };
    case ast::AssignmentOperator::Remainder: {
      current_block->Push(BinOp::Create(left, BinOp::BinaryOperator::Remainder, left, right));
      break;
    };
    case ast::AssignmentOperator::RightShift: {
      current_block->Push(BinOp::Create(left, BinOp::BinaryOperator::RightShift, left, right));
      break;
    };
    case ast::AssignmentOperator::Simple: {
      current_block->Push(CopyOp::Create(left, right));
      break;
    };
    case ast::AssignmentOperator::Subtraction: {
      current_block->Push(BinOp::Create(left, BinOp::BinaryOperator::Subtraction, left, right));
      break;
    };
  }

  return left;
}

std::shared_ptr<Operand> BuildBinaryExpressionIR(
  const std::shared_ptr<ast::BinaryExpression> node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  std::shared_ptr<Operand> left_operand = BuildRExpressionIR(node->left, context, cfg, current_block);
  std::shared_ptr<Operand> right_operand = BuildRExpressionIR(node->right, context, cfg, current_block);
  const std::shared_ptr<const DataType> left_type = GetOperandType(*left_operand);
  const std::shared_ptr<const DataType> right_type = GetOperandType(*right_operand);

  std::shared_ptr<VariableOperand> result_operand;

  if (*right_type == *left_type) {
    result_operand = VariableOperand::Create(context.CreateVariable(left_type, node));
  } else if(node->op == ast::BinaryOperator::Comma) {
    // TODO: check if this is legal
    result_operand = VariableOperand::Create(context.CreateVariable(right_type, node));
  } else {
    const std::shared_ptr<const DataType> result_type = left_type->GetCommonType(*right_type);
    if (*left_type != *result_type) {
      const std::shared_ptr<VariableOperand> casted_left = VariableOperand::Create(context.CreateVariable(result_type));
      current_block->Push(CastOp::Create(casted_left, left_operand));
      left_operand = casted_left;
    }
    if (*right_type != *result_type) {
      const std::shared_ptr<VariableOperand> casted_right = VariableOperand::Create(context.CreateVariable(result_type));
      current_block->Push(CastOp::Create(casted_right, right_operand));
      right_operand = casted_right;
    }
    result_operand = VariableOperand::Create(context.CreateVariable(result_type, node));
  }

  switch (node->op) {
    case ast::BinaryOperator::Addition: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::Addition, left_operand, right_operand));
      break;
    }
    case ast::BinaryOperator::BitwiseAnd: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::BitwiseAnd, left_operand, right_operand));
      break;
    };
    case ast::BinaryOperator::BitwiseOr: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::BitwiseOr, left_operand, right_operand));
      break;
    };
    case ast::BinaryOperator::BitwiseXor: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::BitwiseXor, left_operand, right_operand));
      break;
    };
    case ast::BinaryOperator::Comma: {
      current_block->Push(CopyOp::Create(result_operand, right_operand));
      break;
    };
    case ast::BinaryOperator::Division: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::Division, left_operand, right_operand));
      break;
    }
    case ast::BinaryOperator::Equality: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::Equality, left_operand, right_operand));
      break;
    };
    case ast::BinaryOperator::GreaterThan: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::GreaterThan, left_operand, right_operand));
      break;
    };
    case ast::BinaryOperator::GreaterThanOrEqual: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::GreaterThanOrEqual, left_operand, right_operand));
      break;
    };
    case ast::BinaryOperator::Inequality: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::Inequality, left_operand, right_operand));
      break;
    };
    case ast::BinaryOperator::LeftShift: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::LeftShift, left_operand, right_operand));
      break;
    };
    case ast::BinaryOperator::LessThan: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::LessThan, left_operand, right_operand));
      break;
    };
    case ast::BinaryOperator::LessThanOrEqualTo: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::LessThanOrEqualTo, left_operand, right_operand));
      break;
    };
    case ast::BinaryOperator::Multiplication: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::Multiplication, left_operand, right_operand));
      break;
    }
    case ast::BinaryOperator::Remainder: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::Remainder, left_operand, right_operand));
      break;
    };
    case ast::BinaryOperator::RightShift: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::RightShift, left_operand, right_operand));
      break;
    };
    case ast::BinaryOperator::Subtraction: {
      current_block->Push(BinOp::Create(result_operand, BinOp::BinaryOperator::Subtraction, left_operand, right_operand));
      break;
    }
  }

  return result_operand;
}

std::shared_ptr<Operand> BuildCallExpressionIR(
  const std::shared_ptr<ast::CallExpression> node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  // Get the function
  std::shared_ptr<FunctionSymbol> function;
  switch (node->callee->node_type) {
    case ast::Node::Type::Identifier:
      function = context.ResolveFunction(
        std::static_pointer_cast<ast::Identifier>(node->callee)->name);
      break;
    default:
      // TODO(Lyrositor) Uncomment once exceptions are fixed
      //throw Exception("Invalid callee node type for function call");
      throw std::domain_error("Invalid callee node type for function call");
  }

  // Create the return variable
  const std::shared_ptr<const Variable>
    tmp_var = context.CreateVariable(function->GetReturnType(), node);
  std::shared_ptr<VariableOperand>
    tmp_operand = VariableOperand::Create(tmp_var);

  // Add the parameters
  std::vector<std::shared_ptr<Operand>> args;
  for (auto arg_node : node->arguments) {
    args.push_back(BuildRExpressionIR(arg_node, context, cfg, current_block));
  }

  // Add the call operation to the current basic block
  current_block->Push(CallOp::Create(tmp_operand, function, args));

  return tmp_operand;
}

std::shared_ptr<Operand> BuildLogicalExpressionIR(
    const std::shared_ptr<ast::LogicalExpression> node,
    Context &context,
    std::shared_ptr<ControlFlowGraph> &cfg,
    std::shared_ptr<BasicBlock> &current_block
) {
  std::shared_ptr<BasicBlock> right_block = cfg->CreateBasicBlock();
  std::shared_ptr<BasicBlock> right_block_head = right_block;
  const std::shared_ptr<BasicBlock> next_block = cfg->CreateBasicBlock();

  std::shared_ptr<Operand> left_operand = BuildRExpressionIR(node->left, context, cfg, current_block);
  std::shared_ptr<Operand> right_operand = BuildRExpressionIR(node->right, context, cfg, right_block);

  const std::shared_ptr<const DataType> left_type = GetOperandType(*left_operand);
  const std::shared_ptr<const DataType> right_type = GetOperandType(*right_operand);

  std::shared_ptr<VariableOperand> result_operand;

  if (*right_type == *left_type) {
    result_operand = VariableOperand::Create(context.CreateVariable(left_type, node));
  } else {
    const std::shared_ptr<const DataType> result_type = left_type->GetCommonType(*right_type);
    if (*left_type != *result_type) {
      const std::shared_ptr<VariableOperand> casted_left = VariableOperand::Create(context.CreateVariable(result_type));
      current_block->Push(CastOp::Create(casted_left, left_operand));
      left_operand = casted_left;
    }
    if (*right_type != *result_type) {
      const std::shared_ptr<VariableOperand> casted_right = VariableOperand::Create(context.CreateVariable(result_type));
      right_block->Push(CastOp::Create(casted_right, right_operand));
      right_operand = casted_right;
    }
    result_operand = VariableOperand::Create(context.CreateVariable(result_type, node));
  }

  current_block->Push(CopyOp::Create(result_operand, left_operand));
  right_block->Push(CopyOp::Create(result_operand, right_operand));

  // Branching
  switch (node->op) {
    case ast::LogicalOperator ::LogicalOr: {
      current_block->SetConditionalJump(result_operand, next_block, right_block_head);
      break;
    }
    case ast::LogicalOperator ::LogicalAnd: {
      current_block->SetConditionalJump(result_operand, right_block_head, next_block);
      break;
    }
  }

  right_block->SetJump(next_block);

  current_block = next_block;

  return result_operand;
}


std::shared_ptr<Operand> BuildUnaryExpressionIR(
  const std::shared_ptr<ast::UnaryExpression> node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  if (node->op == ast::UnaryOperator::PostfixDecrement
    || node->op == ast::UnaryOperator::PostfixIncrement
    || node->op == ast::UnaryOperator::PrefixDecrement
    || node->op == ast::UnaryOperator::PrefixIncrement) {

    if (node->expression->node_type != ast::Node::Type::Identifier
      && node->expression->node_type != ast::Node::Type::SubscriptExpression) {
      throw std::runtime_error("Address operation can only be applied on L-Value");
    }

    std::shared_ptr<WritableOperand> expr = BuildLExpressionIR(
      std::static_pointer_cast<ast::LExpression>(node->expression),
      context,
      cfg,
      current_block);
    const std::shared_ptr<const DataType> expr_type = GetOperandType(*expr);

    std::shared_ptr<WritableOperand> result_operand;

    switch (node->op) {
      case ast::UnaryOperator::PostfixDecrement: {
        result_operand = VariableOperand::Create(context.CreateVariable(expr_type, node));
        current_block->Push(CopyOp::Create(result_operand, expr));
        current_block->Push(UnaryOp::Create(expr, UnaryOp::UnaryOperator::Decrement, expr));
        break;
      }
      case ast::UnaryOperator::PostfixIncrement: {
        result_operand = VariableOperand::Create(context.CreateVariable(expr_type, node));
        current_block->Push(CopyOp::Create(result_operand, expr));
        current_block->Push(UnaryOp::Create(expr, UnaryOp::UnaryOperator::Increment, expr));
        break;
      }
      case ast::UnaryOperator::PrefixDecrement: {
        result_operand = expr;
        current_block->Push(UnaryOp::Create(expr, UnaryOp::UnaryOperator::Decrement, expr));
        break;
      }
      case ast::UnaryOperator::PrefixIncrement: {
        result_operand = expr;
        current_block->Push(UnaryOp::Create(expr, UnaryOp::UnaryOperator::Increment, expr));
        break;
      }
      default: {
        throw std::domain_error("Unexpected value for `node->op` in `BuildUnaryExpressionIR`");
      }
    }
    return result_operand;
  }

  const std::shared_ptr<Operand> expr = BuildRExpressionIR(node->expression, context, cfg, current_block);
  const std::shared_ptr<const DataType> expr_type = GetOperandType(*expr);

  std::shared_ptr<VariableOperand> result_operand;

  switch (node->op) {
    case ast::UnaryOperator::UnaryMinus: {
      result_operand = VariableOperand::Create(context.CreateVariable(expr_type, node));
      current_block->Push(UnaryOp::Create(result_operand, UnaryOp::UnaryOperator::UnaryMinus, expr));
      break;
    }
    case ast::UnaryOperator::AddressOf: {
      if (node->expression->node_type != ast::Node::Type::Identifier
        && node->expression->node_type != ast::Node::Type::SubscriptExpression) {
        throw std::runtime_error("Address operation can only be applied on L-Value");
      }
      result_operand = VariableOperand::Create(context.CreateVariable(GetUsizeType(), node));
      current_block->Push(UnaryOp::Create(result_operand, UnaryOp::UnaryOperator::AddressOf, expr));
      break;
    }
    case ast::UnaryOperator::BitwiseComplement: {
      result_operand = VariableOperand::Create(context.CreateVariable(expr_type, node));
      current_block->Push(UnaryOp::Create(result_operand, UnaryOp::UnaryOperator::BitwiseComplement, expr));
      break;
    }
    case ast::UnaryOperator::Indirection: {
      // Implement it to achieve an effect similar to `expr[0]`.
      throw std::runtime_error("Not implemented: BuildUnaryExpressionIR for Indirection");
    }
    case ast::UnaryOperator::LogicalNegation: {
      result_operand = VariableOperand::Create(context.CreateVariable(expr_type, node));
      current_block->Push(UnaryOp::Create(result_operand, UnaryOp::UnaryOperator::LogicalNegation, expr));
      break;
    }
    case ast::UnaryOperator::UnaryPlus: {
      result_operand = VariableOperand::Create(context.CreateVariable(GetInt64Type(), node));
      current_block->Push(CastOp::Create(result_operand, expr));
      break;
    }
    default: {
      throw std::domain_error("Unexpected value for node.op in `BuildUnaryExpressionIR`");
    }
  }

  return result_operand;
}

std::shared_ptr<Operand> BuildConditionalExpressionIR(
  const std::shared_ptr<ast::ConditionalExpression> node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  std::shared_ptr<BasicBlock> consequence_block = cfg->CreateBasicBlock();
  std::shared_ptr<BasicBlock> consequence_block_head = consequence_block;
  std::shared_ptr<BasicBlock> alternative_block = cfg->CreateBasicBlock();
  std::shared_ptr<BasicBlock> alternative_block_head = alternative_block;
  const std::shared_ptr<BasicBlock> next_block = cfg->CreateBasicBlock();

  const std::shared_ptr<Operand> test_operand = BuildRExpressionIR(node->test, context, cfg, current_block);
  const std::shared_ptr<Operand>
    consequence_operand = BuildRExpressionIR(node->consequence, context, cfg, consequence_block);
  const std::shared_ptr<Operand>
    alternative_operand = BuildRExpressionIR(node->alternative, context, cfg, alternative_block);

  const std::shared_ptr<const DataType> consequence_type = GetOperandType(*consequence_operand);
  const std::shared_ptr<const DataType> alternative_type = GetOperandType(*alternative_operand);
  if (alternative_type->GetType() != consequence_type->GetType()) { // TODO: Deep equality
    throw std::runtime_error("Incompatible types in `BuildConditionalExpressionIR`");
  }

  const std::shared_ptr<const Variable> result_var = context.CreateVariable(consequence_type, node);
  std::shared_ptr<VariableOperand> result_operand = VariableOperand::Create(result_var);
  consequence_block->Push(CopyOp::Create(result_operand, consequence_operand));
  alternative_block->Push(CopyOp::Create(result_operand, alternative_operand));

  current_block->SetConditionalJump(test_operand, consequence_block_head, alternative_block_head);
  consequence_block->SetJump(next_block);
  alternative_block->SetJump(next_block);

  current_block = next_block;

  return result_operand;
}

std::shared_ptr<VariableOperand> BuildIdentifierIR(
  const std::shared_ptr<ast::Identifier> node,
  Context &context
) {
  return VariableOperand::Create(context.ResolveVariable(node->name));
}

std::shared_ptr<IndirectOperand> BuildSubscriptExpressionIR(
  const std::shared_ptr<ast::SubscriptExpression> node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  std::shared_ptr<Operand> base_operand = BuildRExpressionIR(node->array, context, cfg, current_block);
  std::shared_ptr<Operand> offset_operand = BuildRExpressionIR(node->index, context, cfg, current_block);

  if (base_operand->operand_type == Operand::Type::Indirect) {
    throw std::runtime_error("Not implemented: chained indirections");
  }

  std::shared_ptr<const DataType> base_type = GetOperandType(*base_operand);
  std::shared_ptr<const DataType> offset_type = GetOperandType(*offset_operand);
  std::shared_ptr<const DataType> item_type;

  switch(base_type->GetType()) {
    case DataType::Type::Array: {
      item_type = std::static_pointer_cast<const ArrayDataType>(base_type)->GetItemType();
      break;
    }
    case DataType::Type::Pointer: {
      item_type = std::static_pointer_cast<const PointerDataType>(base_type)->GetItemType();
      break;
    }
    default: {
      throw std::domain_error("Unexpected value for `GetOperandType(base_operand)` in `BuildSubscriptExpressionIR`.");
    }
  }

  // Normalize base to a pointer
  std::shared_ptr<const DataType> pointer_type = PointerDataType::Create(item_type);
  if (*base_type != *pointer_type) {
    if(base_type->IsCastableTo(*pointer_type)) {
      const std::shared_ptr<VariableOperand> casted_base = VariableOperand::Create(context.CreateVariable(pointer_type));
      current_block->Push(CastOp::Create(casted_base, base_operand));
      base_operand = casted_base;
    } else {
      throw std::runtime_error("Unable to cast to valid pointer");
    }
  }
  // Normalize offset to usize
  std::shared_ptr<const DataType> usize_type = GetInt64Type();
  if (*offset_type != *usize_type) {
    if(offset_type->IsCastableTo(*usize_type)) {
      const std::shared_ptr<VariableOperand> casted_offset = VariableOperand::Create(context.CreateVariable(usize_type));
      current_block->Push(CastOp::Create(casted_offset, offset_operand));
      offset_operand = casted_offset;
    } else {
      throw std::runtime_error("Unable to cast to usize");
    }
  }

  std::shared_ptr<VariableOperand> resolved_address = VariableOperand::Create(context.CreateVariable(pointer_type));
  current_block->Push(BinOp::Create(resolved_address, BinOp::BinaryOperator::Addition, base_operand, offset_operand));
  return IndirectOperand::Create(resolved_address);
}

std::shared_ptr<Operand> BuildInt64LiteralIR(
  const std::shared_ptr<ast::Int64Literal> node,
  Context &context
) {
  UNUSED(context);
  return ConstantOperand::Create(node->value);
}

std::shared_ptr<Operand> BuildUint8LiteralIR(
  const std::shared_ptr<ast::Uint8Literal> node,
  Context &context
) {
  UNUSED(context);
  return ConstantOperand::Create(node->value);
}

void BuildWhileStatementIR(
  const ast::WhileStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  std::shared_ptr<BasicBlock> test_block = cfg->CreateBasicBlock();
  std::shared_ptr<BasicBlock> test_block_head = test_block;
  std::shared_ptr<BasicBlock> body_block = cfg->CreateBasicBlock();
  std::shared_ptr<BasicBlock> body_block_head = body_block;
  std::shared_ptr<BasicBlock> next_block = cfg->CreateBasicBlock();

  std::shared_ptr<Operand> test_operand = BuildRExpressionIR(node.condition, context, cfg, test_block);
  BuildStatementIR(*node.body, context, cfg, body_block);

  current_block->SetJump(test_block_head);
  test_block->SetConditionalJump(test_operand, body_block_head, next_block);
  if (body_block->GetType() == BasicBlock::Type::Incomplete) {
    body_block->SetJump(test_block_head);
  }
  current_block = next_block;
}

void BuildForStatementIR(
  const ast::ForStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  if (node.initializer != nullptr) {
    switch (node.initializer->node_type) {
      case ast::Node::Type::DeclarationForInitializer : {
        std::shared_ptr<ast::DeclarationForInitializer>
          initializer = std::static_pointer_cast<ast::DeclarationForInitializer>(node.initializer);
        BuildVariableDeclarationIR(*initializer->declaration, context, cfg, current_block);
        break;
      }
      case ast::Node::Type::ExpressionForInitializer : {
        std::shared_ptr<ast::ExpressionForInitializer>
          initializer = std::static_pointer_cast<ast::ExpressionForInitializer>(node.initializer);
        BuildRExpressionIR(initializer->expression, context, cfg, current_block);
        break;
      }
      default: {
        throw std::domain_error("Unexpected Node::Type of ForInitializer in build_ir.");
      }
    }
  }

  std::shared_ptr<BasicBlock> test_block = cfg->CreateBasicBlock();
  std::shared_ptr<BasicBlock> test_block_head = test_block;
  std::shared_ptr<BasicBlock> update_block = cfg->CreateBasicBlock();
  std::shared_ptr<BasicBlock> update_block_head = update_block;
  std::shared_ptr<BasicBlock> body_block = cfg->CreateBasicBlock();
  std::shared_ptr<BasicBlock> body_block_head = body_block;
  std::shared_ptr<BasicBlock> next_block = cfg->CreateBasicBlock();
  if (node.update != nullptr) {
    BuildRExpressionIR(node.update, context, cfg, update_block);
  }
  BuildStatementIR(*node.body, context, cfg, body_block);

  current_block->SetJump(test_block_head);
  if (body_block->GetType() == BasicBlock::Type::Incomplete) {
    body_block->SetJump(update_block_head);
    update_block->SetJump(test_block_head);
  }

  if(node.test == nullptr) {
    test_block->SetJump(body_block_head);
  } else {
    std::shared_ptr<Operand> test_operand = BuildRExpressionIR(node.test, context, cfg, test_block);
    test_block->SetConditionalJump(test_operand, body_block_head, next_block);
    current_block = next_block;
  }
}

void BuildIfStatementIR(
  const ast::IfStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  std::shared_ptr<Operand> test_operand = BuildRExpressionIR(node.test, context, cfg, current_block);
  std::shared_ptr<BasicBlock> next_block = cfg->CreateBasicBlock();
  bool is_next_block_reachable = false;

  std::shared_ptr<BasicBlock> consequence = cfg->CreateBasicBlock();
  std::shared_ptr<BasicBlock> consequence_head = consequence;
  BuildStatementIR(*node.consequence, context, cfg, consequence);
  if (consequence->GetType() == BasicBlock::Type::Incomplete) {
    consequence->SetJump(next_block);
    is_next_block_reachable = true;
  }

  if (node.alternative == nullptr) {
    current_block->SetConditionalJump(test_operand, consequence_head, next_block);
    is_next_block_reachable = true;
  } else {
    std::shared_ptr<BasicBlock> alternative = cfg->CreateBasicBlock();
    std::shared_ptr<BasicBlock> alternative_head = alternative;
    BuildStatementIR(*node.alternative, context, cfg, alternative);
    if (alternative->GetType() == BasicBlock::Type::Incomplete) {
      alternative->SetJump(next_block);
      is_next_block_reachable = true;
    }
    current_block->SetConditionalJump(test_operand, consequence_head, alternative_head);
  }

  if (is_next_block_reachable) {
    current_block = next_block;
  }
}

void BuildReturnStatementIR(
  const ast::ReturnStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  if (node.expression == nullptr) {
    current_block->SetReturn(nullptr);
  } else {
    const std::shared_ptr<Operand> expr = BuildRExpressionIR(node.expression, context, cfg, current_block);
    current_block->SetReturn(expr);
  }
}

void BuildNullStatementIR(
  const ast::NullStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  // No-op
  UNUSED(node);
  UNUSED(context);
  UNUSED(cfg);
  UNUSED(current_block);
}
}  // namespace ir
}  // namespace comp
