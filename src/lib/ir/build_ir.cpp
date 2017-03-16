#include <comp/ir/build_ir.h>

#include <iostream>
#include <memory>

#include <comp/ir/builtins.h>
#include <comp/ir/op.h>

namespace comp {
namespace ir {
void BuildProgramIR(std::shared_ptr<const ast::Program> node) {
  RootContext context = CreateRootContextWithBuiltIns();
  for (auto declaration : node->body) {
    switch (declaration->nodeType) {
      case ast::Node::Type::Function: {
        std::shared_ptr<ast::Function> e = std::static_pointer_cast<ast::Function>(declaration);
        BuildFunctionIR(*e, context);
        break;
      }
      default: {
        throw std::domain_error("Unexpected value for `declaration->nodeType`");
      }
    }
  }
}

void BuildFunctionIR(const ast::Function &node, Context &context) {
  if (node.body == nullptr) {
    // TODO: Add declaration to context
  } else {
    std::shared_ptr<BasicBlock> first_block = BasicBlock::create();
    std::shared_ptr<BasicBlock> current_block = first_block;
    // TODO: context.RegisterVariable(arg1, arg1Type)
    BuildBlockStatementIR(*node.body, context, current_block);
  }
}

void BuildStatementIR(
  const ast::Statement &node,
  Context &context,
  std::shared_ptr<BasicBlock> &current_block
) {
  switch (node.nodeType) {
    case ast::Node::Type::BlockStatement: {
      BuildBlockStatementIR(
        static_cast<const ast::BlockStatement &>(node),
        context,
        current_block
      );
      break;
    }
    case ast::Node::Type::ExpressionStatement: {
      BuildExpressionStatementIR(
        static_cast<const ast::ExpressionStatement &>(node),
        context,
        current_block
      );
      break;
    }
    default: {
      throw std::domain_error("Unexpected value for `node.nodeType`");
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
  const ast::Expression &node,
  Context &context,
  std::shared_ptr<BasicBlock> &current_block
) {
  switch (node.nodeType) {
    case ast::Node::Type::Identifier: {
      return BuildIdentifierRValueIR(
        static_cast<const ast::Identifier &>(node),
        context
      );
    }
    case ast::Node::Type::BinaryExpression: {
      return BuildBinaryExpressionRValueIR(
        static_cast<const ast::BinaryExpression &>(node),
        context,
        current_block
      );
    }
    default: {
      throw std::domain_error("Unexpected value for `node.expression->nodeType`");
    }
  }
}

// TODO: handle mismatched types
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
      current_block->Push(std::shared_ptr<Add>(new Add(r_value, left, right)));
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
}
}
