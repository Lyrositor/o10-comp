#include <comp/ast.h>
#include <comp/ir/build_ir.h>
#include <memory>
#include <iostream>
#include <comp/ir/variable.h>
#include <comp/ir/context.h>
#include <comp/ir/op.h>
#include <comp/ir/basic_block.h>

namespace comp {
namespace ir {
void buildProgramIR(std::shared_ptr<const ast::Program> node) {
  for (auto declaration : node->body) {
    switch (declaration->nodeType) {
      case ast::Node::Type::Function: {
        std::shared_ptr<ast::Function> e = std::static_pointer_cast<ast::Function>(declaration);
        buildFunctionIR(*e);
        break;
      }
      default: {
        throw std::domain_error("Unexpected value for `declaration->nodeType`");
      }
    }
  }
}

void buildFunctionIR(const ast::Function &node) {
  if (node.body == nullptr) {

  } else {
    ir::RootContext context;
    std::shared_ptr<BasicBlock> firstBlock = ir::BasicBlock::create();
    std::shared_ptr<BasicBlock> currentBlock = firstBlock;
    // TODO: context.registerVariable(arg1, arg1Type)
    buildBlockStatementIR(*node.body, context, currentBlock);
  }
}

void buildStatementIR(
  const ast::Statement &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &currentBlock
) {
  switch (node.nodeType) {
    case ast::Node::Type::BlockStatement: {
      buildBlockStatementIR(static_cast<const ast::BlockStatement &>(node), context, currentBlock);
      break;
    }
    case ast::Node::Type::ExpressionStatement: {
      buildExpressionStatementIR(static_cast<const ast::ExpressionStatement &>(node), context, currentBlock);
      break;
    }
    default: {
      throw std::domain_error("Unexpected value for `node.nodeType`");
    }
  }
}

void buildBlockStatementIR(
  const ast::BlockStatement &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &currentBlock
) {
  std::unique_ptr<ir::ChildContext> childContext = context.fork();
  for (auto statement : node.body) {
    buildStatementIR(*statement, *childContext, currentBlock);
  }
  context.join(std::move(childContext));
}

void buildExpressionStatementIR(
  const ast::ExpressionStatement &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &currentBlock
) {
  buildExpressionRValueIR(*node.expression, context, currentBlock);
}

std::shared_ptr<ir::Variable> buildExpressionRValueIR(
  const ast::Expression &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &currentBlock
) {
  switch (node.nodeType) {
    case ast::Node::Type::Identifier: {
      return buildIdentifierRValueIR(static_cast<const ast::Identifier &>(node), context);
    }
    case ast::Node::Type::BinaryExpression: {
      return buildBinaryExpressionRValueIR(static_cast<const ast::BinaryExpression &>(node), context, currentBlock);
    }
    default: {
      throw std::domain_error("Unexpected value for `node.expression->nodeType`");
    }
  }
}

// TODO: handle mismatched types
std::shared_ptr<ir::Variable> buildBinaryExpressionRValueIR(
  const ast::BinaryExpression &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &currentBlock
) {
  const std::shared_ptr<ir::Variable> left = buildExpressionRValueIR(*node.left, context, currentBlock);
  const std::shared_ptr<ir::Variable> right = buildExpressionRValueIR(*node.right, context, currentBlock);
  const std::shared_ptr<const DataType> leftType = left->getDataType();
  const std::shared_ptr<const DataType> rightType = right->getDataType();
  if (leftType != rightType) {
    throw std::runtime_error("Mismatched types for left and right operands");
  }
  const std::shared_ptr<ir::Variable> rValue = context.createVariable(leftType);

  switch (node.op) {
    case ast::BinaryOperator::Addition: {
      currentBlock->push(std::shared_ptr<ir::Add>(new Add(rValue, left, right)));
      break;
    }
    default: {
      throw std::domain_error("Unexpected value for node.op");
    }
  }
  return rValue;
}

std::shared_ptr<ir::Variable> buildIdentifierRValueIR(
  const ast::Identifier &node,
  ir::Context &context
) {
  std::shared_ptr<ir::Variable> rValue = context.resolveVariable(node.name);
  return rValue;
}

std::shared_ptr<ir::Variable> buildIdentifierLValueIR(const ast::Identifier &node, ir::Context &context) {
  std::shared_ptr<ir::Variable> lValue = context.resolveVariable(node.name);
  return lValue;
}
}
}
