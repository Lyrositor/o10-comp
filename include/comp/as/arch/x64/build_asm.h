#include <memory>

#include <vector>

#include <comp/as/arch/block_table.h>
#include <comp/as/arch/variables_table.h>
#include <comp/as/ast.h>
#include <comp/ir/basic_block.h>
#include <comp/ir/program.h>

namespace comp {
namespace as {
namespace arch {
namespace x64 {
std::shared_ptr<as::ast::Program> BuildProgram(const ir::Program &node);

void BuildFunction(
  std::shared_ptr<const ir::FunctionSymbol> node,
  std::vector<std::shared_ptr<ast::Statement>> &body);

void BuildBasicBlock(
  std::shared_ptr<ir::BasicBlock> block,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const BlockTable &block_table,
  const VariablesTable &variables_table);

void BuildOp(
  std::shared_ptr<ir::Op> op,
  std::shared_ptr<ir::BasicBlock> block,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const BlockTable &block_table,
  const VariablesTable &variables_table);

void BuildBinOp(
  std::shared_ptr<ir::BinOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const VariablesTable &variables_table);

void BuildCallOp(
  std::shared_ptr<ir::CallOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const VariablesTable &variables_table);

void BuildCastOp(
  std::shared_ptr<ir::CastOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const VariablesTable &variables_table);

void BuildCopyOp(
  std::shared_ptr<ir::CopyOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const VariablesTable &variables_table);

void BuildNoOp(
  std::shared_ptr<ir::NoOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const VariablesTable &variables_table);

void BuildReturnOp(
  std::shared_ptr<ir::ReturnOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const VariablesTable &variables_table);

void BuildTestOp(
  std::shared_ptr<ir::TestOp> op,
  std::shared_ptr<ir::BasicBlock> block,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const BlockTable &block_table,
  const VariablesTable &variables_table);

void BuildUnaryOp(
  std::shared_ptr<ir::UnaryOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const VariablesTable &variables_table);

std::shared_ptr<ast::Operand> BuildOperand(
  std::shared_ptr<ir::Operand> op,
  const VariablesTable &variables_table);
}  // namespace x64
}  // namespace arch
}  // namespace as
}  // namespace comp
