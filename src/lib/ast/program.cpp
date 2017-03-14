#include <comp/ast/program.h>

namespace comp {
namespace ast {
Program::Program(
  std::vector<std::shared_ptr<Declaration>> body,
  std::shared_ptr<SourceLocation> location
) :
  Node(Node::Type::Program, location),
  body(body) {
}

Program::~Program() {
}
}
}
