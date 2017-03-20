#include <comp/as/ast/operand.h>

namespace comp {
namespace as {
namespace ast {
Operand::Operand(
  Type node_type
) :
  Node(node_type) {
}

Operand::~Operand() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
