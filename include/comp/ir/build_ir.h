#pragma once

#include "comp/ast.h"
#include "comp/ir/basic_block.h"
#include "comp/ir/context.h"
#include "comp/ir/op.h"
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


void BuildVariableDeclarationIR(
  const ast::VariableDeclaration &node,
  ir::Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

// R-values
std::shared_ptr<Operand> BuildExpressionIR(
  const std::shared_ptr<ast::RExpression> node,
  ir::Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

std::shared_ptr<Operand> BuildBinaryExpressionIR(
  const std::shared_ptr<ast::BinaryExpression> node,
  ir::Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

std::shared_ptr<Operand> BuildUnaryExpressionIR(
  const std::shared_ptr<ast::UnaryExpression> node,
  ir::Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

std::shared_ptr<Operand> BuildIdentifierRValueIR(
  const std::shared_ptr<ast::Identifier> node,
  ir::Context &context
);

// L-values
std::shared_ptr<VariableOperand> BuildIdentifierLValueIR(
  const ast::Identifier &node,
  ir::Context &context
);

void BuildWhileStatementIR(
  const ast::WhileStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

void BuildForStatementIR(
  const ast::ForStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

void BuildIfStatementIR(
  const ast::IfStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

void BuildNullStatementIR(
  const ast::NullStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

void BuildReturnStatementIR(
  const ast::ReturnStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

}  // namespace ir
}  // namespace comp
