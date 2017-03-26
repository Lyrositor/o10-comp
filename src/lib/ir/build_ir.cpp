#include <comp/ir/build_ir.h>

#include <comp/ir/builtins.h>
#include <comp/ir/op.h>

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
    std::shared_ptr<const DataType> data_type = BuildDataTypeIR(
      context,
      parameter->data_type);
    parameters.push_back(Variable::Create(data_type, parameter->declarator));
  }

  // Create the IR of the function's return type
  std::shared_ptr<const DataType> return_type = BuildDataTypeIR(
    context,
    node.return_type);

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
  for (auto parameter : parameters) {
    variables_table[parameter->GetDeclarator()->GetName()] = parameter;
  }
  ChildContext function_context(
    context, SymbolTable({}, variables_table, {}), {});

  // Generate the function block's IR
  std::shared_ptr<BasicBlock> first_block = BasicBlock::create();
  BuildBlockStatementIR(*node.body, function_context, first_block);
  function->SetBody(first_block);
  function->SetLocalVariables(function_context.GetVariables());

  return function;
}

std::shared_ptr<const DataType> BuildDataTypeIR(
  const Context & context,
  std::shared_ptr<ast::DataType> data_type_node
) {
  std::shared_ptr<const DataType> data_type;
  switch (data_type_node->node_type) {
    case ast::Node::Type::ArrayDataType: {
      std::shared_ptr<ast::ArrayDataType>
        e = std::static_pointer_cast<ast::ArrayDataType>(data_type_node);

      // Check if the array size was specified
      // If it was specified, view this as a segment of contiguous memory (an
      // array); if not, view it as an ordinary pointer.
      if (e->size != nullptr) {
        size_t size;
        switch (e->size->node_type) {
          case ast::Node::Type::Int64Literal:
            size = static_cast<size_t>(
              std::static_pointer_cast<ast::Int64Literal>(e->size)->value);
            break;
          case ast::Node::Type::Uint8Literal:
            size = static_cast<size_t>(
              std::static_pointer_cast<ast::Uint8Literal>(e->size)->value);
            break;
          default:
            // Currently, we only support literals to specify array size
            throw std::runtime_error("Array length not a literal");
        }
        data_type = ArrayDataType::Create(
          BuildDataTypeIR(context, e->item_type),
          size);
      } else {
        data_type = PointerDataType::Create(
          BuildDataTypeIR(context, e->item_type));
      }
      break;
    }
    case ast::Node::Type::LiteralDataType: {
      std::shared_ptr<ast::LiteralDataType>
        e = std::static_pointer_cast<ast::LiteralDataType>(data_type_node);
      data_type = context.ResolveDataType(e->identifier->name);
      break;
    }
    default: {
      throw std::domain_error("Unexpected data type");
    }
  }
  return data_type;
}

void BuildStatementIR(
  const ast::Statement &node,
  Context &context,
  std::shared_ptr<BasicBlock> &current_block
) {
  switch (node.node_type) {
    case ast::Node::Type::BlockStatement: {
      BuildBlockStatementIR(
        static_cast<const ast::BlockStatement &>(node),
        context,
        current_block);
      break;
    }
    case ast::Node::Type::ExpressionStatement: {
      BuildExpressionStatementIR(
        static_cast<const ast::ExpressionStatement &>(node),
        context,
        current_block);
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
  std::shared_ptr<BasicBlock> &current_block
) {
  std::unique_ptr<ChildContext> childContext = context.Fork();
  for (auto statement : node.body) {
    BuildStatementIR(*statement, *childContext, current_block);
  }
  context.Join(std::move(childContext));
}

void BuildExpressionStatementIR(
  const ast::ExpressionStatement &node,
  Context &context,
  std::shared_ptr<BasicBlock> &current_block
) {
  BuildExpressionRValueIR(*node.expression, context, current_block);
}

std::shared_ptr<const Variable> BuildExpressionRValueIR(
  const ast::RExpression &node,
  Context &context,
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
  std::shared_ptr<BasicBlock> &current_block
) {
  const std::shared_ptr<const Variable> left =
    BuildExpressionRValueIR(*node.left, context, current_block);
  const std::shared_ptr<const Variable> right =
    BuildExpressionRValueIR(*node.right, context, current_block);
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
      current_block->Push(Add::Create(
        VariableOperand::Create(r_value),
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
}  // namespace ir
}  // namespace comp
