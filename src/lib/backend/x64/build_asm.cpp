#include <comp/ir/program.h>
#include <comp/backend/x86/build_asm.h>

namespace comp {
namespace backend {
namespace x86 {
std::shared_ptr<as::ast::Program> BuildProgram(const ir::Program &node) {
  std::vector<std::shared_ptr<as::ast::Statement>> body;

  body.push_back(as::ast::TextDirective::Create());

  std::shared_ptr<as::ast::Program> program = as::ast::Program::Create(body);
  return program;
}
}
}
}
