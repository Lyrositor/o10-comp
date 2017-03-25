#pragma once

#include "comp/ast.h"
#include "comp/ir/basic_block.h"
#include "comp/ir/context.h"
#include "comp/ir/program.h"
#include "comp/ir/variable.h"

namespace comp {
namespace ir {
std::shared_ptr<Program> BuildProgramIR(const ast::Program &program_node);

std::shared_ptr<FunctionSymbol> BuildFunctionIR(
  const ast::Function &node, Context &context);

std::shared_ptr<const DataType> BuildDataTypeIR(
  const Context & context,
  std::shared_ptr<ast::DataType> data_type_node);

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
  const ast::RExpression &node,
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
}  // namespace ir
}  // namespace comp
