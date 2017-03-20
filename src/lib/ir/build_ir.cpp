#include <comp/ir/build_ir.h>

#include <comp/ir/builtins.h>
#include <comp/ir/op.h>

namespace comp {
namespace ir {
std::shared_ptr<Program> BuildProgramIR(
  std::shared_ptr<const ast::Program> program_node
) {
  std::shared_ptr<Program> program(new Program());
  RootContext context = CreateRootContextWithBuiltIns();
  for (auto declaration : program_node->body) {
    switch (declaration->node_type) {
      case ast::Node::Type::Function: {
        std::shared_ptr<ast::Function>
          e = std::static_pointer_cast<ast::Function>(declaration);
        std::shared_ptr<FunctionSymbol> function = BuildFunctionIR(*e, context);
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
  std::vector<std::shared_ptr<const Parameter>> parameters;
  for (auto parameter : node.parameters) {
    std::shared_ptr<DataType> data_type;
    switch (parameter->data_type->node_type) {
      case ast::Node::Type::ArrayDataType:
        // TODO(Lyrositor) Handle arrays
        break;
      case ast::Node::Type::LiteralDataType:
        // TODO(Lyrositor) Handle literals
        break;
      default: {
        throw std::domain_error("Unexpected data type for parameter");
      }
    }
    parameters.emplace_back(
      new Parameter(data_type, parameter->identifier->name));
  }

  // Create the IR of the function's return type
  const std::shared_ptr<const DataType> return_type;
  switch (node.return_type->node_type) {
    case ast::Node::Type::ArrayDataType:
      // TODO(Lyrositor) Handle arrays
      break;
    case ast::Node::Type::LiteralDataType:
      // TODO(Lyrositor) Handle literals
      break;
    default: {
      throw std::domain_error("Unexpected data type for parameter");
    }
  }

  // TODO(Lyrositor) Add declaration to context if applicable
  std::shared_ptr<FunctionSymbol> function;
  try {
    function = context.ResolveFunction(node.identifier->name);
  } catch (std::runtime_error &) {
    // Register the function's symbol (without a body initially)
    function = FunctionSymbol::Create(
      parameters, return_type);
    context.RegisterFunction(node.identifier->name, function);
    if (node.body == nullptr) {
      return nullptr;
    }
  }

  // Check that this function isn't being declared twice
  // TODO(Lyrositor) Make sure this is a part of the C standard
  if (node.body == nullptr) {
    throw std::runtime_error("Function was previously declared");
  }
  // TODO(Lyrositor) Check that the signatures match

  // Create the child context
  VariablesTable variables_table;
  for (auto parameter : parameters) {
  }
  // TODO(Lyrositor) Handle `variables` parameter properly
  ChildContext function_context(
    context, SymbolTable({}, variables_table, {}), {});

  // Generate the function block's IR
  std::shared_ptr<BasicBlock> function_block = BasicBlock::create();
  BuildBlockStatementIR(*node.body, function_context, function_block);
  function->SetBody(function_block);

  return function;
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

std::shared_ptr<Variable> BuildExpressionRValueIR(
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
std::shared_ptr<Variable> BuildBinaryExpressionRValueIR(
  const ast::BinaryExpression &node,
  Context &context,
  std::shared_ptr<BasicBlock> &current_block
) {
  const std::shared_ptr<Variable> left =
    BuildExpressionRValueIR(*node.left, context, current_block);
  const std::shared_ptr<Variable> right =
    BuildExpressionRValueIR(*node.right, context, current_block);
  const std::shared_ptr<const DataType> left_type = left->GetDataType();
  const std::shared_ptr<const DataType> right_type = right->GetDataType();
  if (left_type != right_type) {
    throw std::runtime_error("Mismatched types for left and right operands");
  }
  const std::shared_ptr<Variable> r_value = context.CreateVariable(left_type);

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

std::shared_ptr<Variable> BuildIdentifierRValueIR(
  const ast::Identifier &node,
  Context &context
) {
  return context.ResolveVariable(node.name);
}

std::shared_ptr<Variable> BuildIdentifierLValueIR(
  const ast::Identifier &node,
  Context &context
) {
  return context.ResolveVariable(node.name);
}
}  // namespace ir
}  // namespace comp
