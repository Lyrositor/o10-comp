#include <memory>

#include <comp/ir/program.h>
#include <comp/as/ast.h>

namespace comp {
namespace as {
namespace arch {
namespace x64 {
std::shared_ptr<as::ast::Program> BuildProgram(const ir::Program &node);
void BuildFunction(
  std::shared_ptr<const ir::FunctionSymbol> node,
  std::vector<std::shared_ptr<ast::Statement>> &body);
}  // namespace x64
}  // namespace arch
}  // namespace as
}  // namespace comp
