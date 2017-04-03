#include <comp/ir/to_dot.h>

namespace comp {
namespace ir {
std::unique_ptr<dot::ast::Graph> ProgramToDot(const Program &node) {
  return dot::ast::Graph::Create(true, true, nullptr, {});
}
}  // namespace ir
}  // namespace comp
