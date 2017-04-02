#include <memory>

#include <vector>

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
  const std::vector<std::shared_ptr<ast::Statement>> &body,
  VariablesTable &variables_table
);
}  // namespace x64
}  // namespace arch
}  // namespace as
}  // namespace comp
