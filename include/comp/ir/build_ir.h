#pragma once

#include "../ast.h"
#include "basic_block.h"
#include "context.h"
#include "variable.h"

namespace comp {
namespace ir {
void buildProgramIR(const ast::Program &node);

void buildFunctionIR(const ast::Function &node);

// Statements
void buildStatementIR(
  const ast::Statement &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &currentBlock
);

void buildBlockStatementIR(
  const ast::BlockStatement &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &currentBlock
);

void buildExpressionStatementIR(
  const ast::ExpressionStatement &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &currentBlock
);

// R-values
std::shared_ptr<ir::Variable> buildExpressionRValueIR(
  const ast::Expression &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &currentBlock
);

std::shared_ptr<ir::Variable> buildIdentifierRValueIR(
  const ast::Identifier &node,
  ir::Context &context
);

std::shared_ptr<ir::Variable> buildBinaryExpressionRValueIR(
  const ast::BinaryExpression &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &currentBlock
);

// L-values
std::shared_ptr<ir::Variable> buildIdentifierLValueIR(const ast::Identifier &node, ir::Context &context);
}
}
