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
  const ast::Function &node,
  Context &context);

std::shared_ptr<const DataType> ResolveDataTypeType(const ast::DataType &data_type, const Context &context);
std::shared_ptr<const DataType> ResolveDeclaratorType (const std::shared_ptr<const DataType> base_type, const ast::Declarator &declarator);
std::shared_ptr<const DataType> ResolveParameterType (const ast::Parameter &parameter, const Context & context);
std::string ResolveDeclaratorName (const ast::Declarator &declarator);
std::string ResolveParameterName (const ast::Parameter &parameter);

// Statements
void BuildStatementIR(
  const ast::Statement &node,
  ir::Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

void BuildBlockStatementIR(
  const ast::BlockStatement &node,
  ir::Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

void BuildExpressionStatementIR(
  const ast::ExpressionStatement &node,
  ir::Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

// R-values
std::shared_ptr<const ir::Variable> BuildExpressionRValueIR(
  const ast::RExpression &node,
  ir::Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

std::shared_ptr<const ir::Variable> BuildBinaryExpressionRValueIR(
  const ast::BinaryExpression &node,
  ir::Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

std::shared_ptr<const ir::Variable> BuildIdentifierRValueIR(
  const ast::Identifier &node,
  ir::Context &context
);

// L-values
std::shared_ptr<const ir::Variable> BuildIdentifierLValueIR(
  const ast::Identifier &node,
  ir::Context &context
);
}  // namespace ir
}  // namespace comp
