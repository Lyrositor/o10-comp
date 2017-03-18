#include <comp/ast/program.h>

namespace comp {
namespace ast {
std::unique_ptr<Program> Program::Create(
  std::vector<std::shared_ptr<Declaration>> body,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<Program>(new Program(body, location));
}

Program::Program(
  std::vector<std::shared_ptr<Declaration>> body,
  std::shared_ptr<SourceLocation> location
) :
  Node(Type::Program, location), body(body) {
}

Program::~Program() {
}
}  // namespace ast
}  // namespace comp
