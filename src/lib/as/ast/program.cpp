#include <comp/as/ast/program.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<Program> Program::Create(std::vector<std::shared_ptr<Statement>> body) {
  return std::unique_ptr<Program>(new Program(body));
}

Program::Program(
  std::vector<std::shared_ptr<Statement>> body
) :
  Node(Type::Program),
  body(body) {
}

Program::~Program() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
