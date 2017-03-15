#pragma once

#include "../ast.h"
#include "basic_block.h"
#include "context.h"
#include "variable.h"

namespace comp {
namespace ir {
void BuildProgramIR(const ast::Program &node);

void BuildFunctionIR(const ast::Function &node, Context &context);

// Statements
void BuildStatementIR(
  const ast::Statement &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &current_block
);

void BuildBlockStatementIR(
  const ast::BlockStatement &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &current_block
);

void BuildExpressionStatementIR(
  const ast::ExpressionStatement &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &current_block
);

// R-values
std::shared_ptr<ir::Variable> BuildExpressionRValueIR(
  const ast::Expression &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &current_block
);

std::shared_ptr<ir::Variable> BuildIdentifierRValueIR(
  const ast::Identifier &node,
  ir::Context &context
);

std::shared_ptr<ir::Variable> BuildBinaryExpressionRValueIR(
  const ast::BinaryExpression &node,
  ir::Context &context,
  std::shared_ptr<BasicBlock> &current_block
);

// L-values
std::shared_ptr<ir::Variable> BuildIdentifierLValueIR(
  const ast::Identifier &node,
  ir::Context &context
);
}
}
