#include <comp/ir/program.h>
#include <comp/as/ast.h>

namespace comp {
namespace backend {
namespace x86 {
std::shared_ptr<as::ast::Program> BuildProgram(const ir::Program &node);
}
}
}
