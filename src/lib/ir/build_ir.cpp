#include <comp/ir/build_ir.h>

#include <comp/ir/builtins.h>
#include <comp/ir/control_flow_graph.h>
#include <comp/ir/op.h>
#include <comp/utils.h>

namespace comp {
namespace ir {
std::shared_ptr<Program> BuildProgramIR(const ast::Program &program_node) {
  std::shared_ptr<Program> program(new Program());
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
      default: {
        throw std::domain_error("Unexpected node type in root context");
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
    parameters.push_back(Variable::Create(data_type, nullptr)); // TODO: parameter
  }

  // Create the IR of the function's return type
  std::shared_ptr<const DataType> return_type = ResolveDataTypeType(*node.return_type, context);

  // Add declaration to context, if it hasn't already been done
  std::shared_ptr<FunctionSymbol> function;
  try {
    function = context.ResolveFunction(node.identifier->name);
  } catch (std::runtime_error &) {
    // Register the function's symbol (without a body initially)
    function = FunctionSymbol::Create(parameters, return_type);
    context.RegisterFunction(node.identifier->name, function);
    if (node.body == nullptr) {
      return nullptr;
    }
  }

  // Ensure this function is not being declared twice or defined twice
  if (node.body == nullptr) {
    throw std::runtime_error("Function was already declared");
  }
  if (function->GetBody() != nullptr) {
    throw std::runtime_error("Function was already defined");
  }

  // Check that the function signatures match
  if (parameters.size() != function->GetParameters().size()) {
    throw std::runtime_error(
      "Function's parameter list does not match declared parameter list");
  }
  if (return_type != function->GetReturnType()) {
    throw std::runtime_error(
      "Function's return type does not match declared type");
  }
  for (size_t i = 0; i < parameters.size(); i++) {
    if (parameters[i]->GetDataType() !=
      function->GetParameters()[i]->GetDataType()) {
      throw std::runtime_error(
        "Function parameter's type does not match declared type");
    }
  }
  // Create the child context
  VariablesTable variables_table;
  std::set<std::shared_ptr<const Variable>> variables_set;
  for (size_t i = 0; i < node.parameters.size(); i++) {
    std::string parameter_name = ResolveParameterName(*node.parameters[i]);
    if (parameter_name != "") {
      variables_table[parameter_name] = parameters[i];
    }
    variables_set.insert(parameters[i]);
  }
  ChildContext function_context(context, SymbolTable({}, variables_table, {}), variables_set);

  // Generate the function's control flow graph
  std::shared_ptr<ControlFlowGraph> cfg = ControlFlowGraph::Create();
  std::shared_ptr<BasicBlock> source = cfg->GetSource();
  BuildBlockStatementIR(*node.body, function_context, cfg, source);
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
            throw std::runtime_error("Array length not a literal");
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
      throw std::runtime_error("Unexpected node type");
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
        throw std::runtime_error("Cannot specify size");
      }
    }
    case ast::Node::Type::IdentifierDeclarator: {
      return base_type;
    }
    default: {
      throw std::runtime_error("Unexpected node type");
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
      throw std::runtime_error("Unexpected node type");
    }
  }
}

std::string ResolveDeclaratorName(const ast::Declarator &declarator) {
  switch (declarator.node_type) {
    case ast::Node::Type::ArrayDeclarator: {
      return ResolveDeclaratorName(declarator);
    }
    case ast::Node::Type::IdentifierDeclarator: {
      const ast::IdentifierDeclarator
        &identifierDeclarator = static_cast<const ast::IdentifierDeclarator &>(declarator);
      return identifierDeclarator.identifier->name;
    }
    default: {
      throw std::runtime_error("Unexpected node type");
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
      throw std::runtime_error("Unexpected node type");
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
      throw std::domain_error("Unexpected value for `node.node_type`");
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
  BuildExpressionRValueIR(*node.expression, context, cfg, current_block);
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
      std::shared_ptr<const Variable>
        initial_value = BuildExpressionRValueIR(*variable_declarator->initial_value, context, cfg, current_block);
      // TODO: current_block->Push(Op::Copy::Create(variable, initial_value))
      throw new std::runtime_error("Not implemented: initial value, depends on the abstract assembly instruction `Copy`");
    }
  }
}

std::shared_ptr<const Variable> BuildExpressionRValueIR(
  const ast::RExpression &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  switch (node.node_type) {
    case ast::Node::Type::Identifier: {
      return BuildIdentifierRValueIR(
        static_cast<const ast::Identifier &>(node),
        context);
    }
    case ast::Node::Type::BinaryExpression: {
      return BuildBinaryExpressionRValueIR(
        static_cast<const ast::BinaryExpression &>(node),
        context,
        cfg,
        current_block);
    }
    default: {
      throw std::domain_error(
        "Unexpected value for `node.expression->node_type`");
    }
  }
}

// TODO(demurgos) handle mismatched types
std::shared_ptr<const Variable> BuildBinaryExpressionRValueIR(
  const ast::BinaryExpression &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
  const std::shared_ptr<const Variable> left =
    BuildExpressionRValueIR(*node.left, context, cfg, current_block);
  const std::shared_ptr<const Variable> right =
    BuildExpressionRValueIR(*node.right, context, cfg, current_block);
  const std::shared_ptr<const DataType> left_type = left->GetDataType();
  const std::shared_ptr<const DataType> right_type = right->GetDataType();
  if (left_type != right_type) {
    throw std::runtime_error("Mismatched types for left and right operands");
  }
  const std::shared_ptr<const Variable> r_value = context.CreateVariable(
    left_type,
    left->GetDeclarator());

  switch (node.op) {
    case ast::BinaryOperator::Addition: {
      current_block->Push(BinOp::Create(
        VariableOperand::Create(r_value),
        BinOp::BinaryOperator::Addition,
        VariableOperand::Create(left),
        VariableOperand::Create(right)
      ));
      break;
    }
    default: {
      throw std::domain_error("Unexpected value for node.op");
    }
  }
  return r_value;
}

std::shared_ptr<const Variable> BuildIdentifierRValueIR(
  const ast::Identifier &node,
  Context &context
) {
  return context.ResolveVariable(node.name);
}

std::shared_ptr<const Variable> BuildIdentifierLValueIR(
  const ast::Identifier &node,
  Context &context
) {
  return context.ResolveVariable(node.name);
}

void BuildWhileStatementIR(
  const ast::WhileStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
    // Init
    std::shared_ptr<BasicBlock> condition = cfg->CreateBasicBlock();
    std::shared_ptr<BasicBlock> body = cfg->CreateBasicBlock();
    std::shared_ptr<BasicBlock> next = cfg->CreateBasicBlock();
    // Building
    BuildExpressionRValueIR(*node.condition, context, cfg, condition);
    BuildStatementIR(*node.body, context, cfg, body);
    // Branching
    current_block->SetBranchIfTrue(condition);
    condition->SetBranchIfTrue(body);
    condition->SetBranchIfFalse(next);
    body->SetBranchIfTrue(condition);
    // Ending
    current_block = next;
}

void BuildForStatementIR(
  const ast::ForStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
    // Init
    std::shared_ptr<BasicBlock> initialization = cfg->CreateBasicBlock();
    std::shared_ptr<BasicBlock> condition = cfg->CreateBasicBlock();
    std::shared_ptr<BasicBlock> iteration = cfg->CreateBasicBlock();
    std::shared_ptr<BasicBlock> body = cfg->CreateBasicBlock();
    std::shared_ptr<BasicBlock> next = cfg->CreateBasicBlock();
    // Building
    BuildExpressionRValueIR(*node.initialization, context, cfg, initialization);
    BuildExpressionRValueIR(*node.condition, context, cfg, condition);
    BuildExpressionRValueIR(*node.iteration, context, cfg, iteration);
    BuildStatementIR(*node.body, context, cfg, body);
    // Branching
    current_block->SetBranchIfTrue(initialization);
    initialization->SetBranchIfTrue(condition);
    condition->SetBranchIfTrue(body);
    condition->SetBranchIfFalse(next);
    body->SetBranchIfTrue(iteration);
    iteration->SetBranchIfTrue(condition);
    // Ending
    current_block = next;
}

void BuildIfStatementIR(
  const ast::IfStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
    // Init
    std::shared_ptr<BasicBlock> test = cfg->CreateBasicBlock();
    std::shared_ptr<BasicBlock> consequence = cfg->CreateBasicBlock();
    std::shared_ptr<BasicBlock> next = cfg->CreateBasicBlock();
    // Building
    BuildExpressionRValueIR(*node.test, context, cfg, test);
    BuildStatementIR(*node.consequence, context, cfg, consequence);
    // Branching
    current_block->SetBranchIfTrue(test);
    test->SetBranchIfTrue(consequence);
    consequence->SetBranchIfTrue(next);
    if (node.alternative != nullptr) {
      std::shared_ptr<BasicBlock> alternative = cfg->CreateBasicBlock();
      BuildStatementIR(*node.alternative, context, cfg, alternative);
      test->SetBranchIfFalse(alternative);
      alternative->SetBranchIfTrue(next);
    } else {
      test->SetBranchIfFalse(next);
    }
    // Ending
    current_block = next;
}

void BuildReturnStatementIR(
  const ast::ReturnStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
) {
    // Init
    std::shared_ptr<BasicBlock> expression = cfg->CreateBasicBlock();
    std::shared_ptr<BasicBlock> next = cfg->CreateBasicBlock();
    // Building
    BuildExpressionRValueIR(*node.expression, context, cfg, expression);
    // Branching
    current_block->SetBranchIfTrue(expression);
    expression->SetBranchIfTrue(next);
    // Ending
    current_block = next;
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

// End
}  // namespace ir
}  // namespace comp
