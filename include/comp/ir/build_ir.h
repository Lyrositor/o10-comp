#pragma once

#include "comp/ast.h"
#include "comp/ir/op_grah.h"
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
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);

void BuildBlockStatementIR(
  const ast::BlockStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);

void BuildExpressionStatementIR(
  const ast::ExpressionStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);


void BuildVariableDeclarationIR(
  const ast::VariableDeclaration &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);

std::shared_ptr<Operand> BuildRExpressionIR(
  const std::shared_ptr<ast::RExpression> node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);

std::shared_ptr<VariableOperand> BuildLExpressionIR(
  const std::shared_ptr<ast::LExpression> node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);

std::shared_ptr<Operand> BuildAssignmentExpressionIR(
  const std::shared_ptr<ast::AssignmentExpression> node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);

std::shared_ptr<Operand> BuildBinaryExpressionIR(
  const std::shared_ptr<ast::BinaryExpression> node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);

std::shared_ptr<Operand> BuildCallExpressionIR(
  const std::shared_ptr<ast::CallExpression> node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);

std::shared_ptr<Operand> BuildUnaryExpressionIR(
  const std::shared_ptr<ast::UnaryExpression> node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);

std::shared_ptr<Operand> BuildConditionalExpressionIR(
  const std::shared_ptr<ast::ConditionalExpression> node,
  ir::Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block
);

std::shared_ptr<VariableOperand> BuildIdentifierIR(
  const std::shared_ptr<ast::Identifier> node,
  Context &context);

std::shared_ptr<Operand> BuildInt64LiteralIR(
  const std::shared_ptr<ast::Int64Literal> node,
  Context &context);

std::shared_ptr<Operand> BuildUint8LiteralIR(
  const std::shared_ptr<ast::Uint8Literal> node,
  Context &context);

// L-values
std::shared_ptr<VariableOperand> BuildIdentifierLValueIR(
  const ast::Identifier &node,
  Context &context);

void BuildWhileStatementIR(
  const ast::WhileStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);

void BuildForStatementIR(
  const ast::ForStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);

void BuildIfStatementIR(
  const ast::IfStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);

void BuildNullStatementIR(
  const ast::NullStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);

void BuildReturnStatementIR(
  const ast::ReturnStatement &node,
  Context &context,
  std::shared_ptr<ControlFlowGraph> &cfg,
  std::shared_ptr<BasicBlock> &current_block);

}  // namespace ir
}  // namespace comp
