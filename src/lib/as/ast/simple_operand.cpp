#include <comp/as/ast/simple_operand.h>

namespace comp {
namespace as {
namespace ast {
SimpleOperand::SimpleOperand(
  Type node_type
) :
  Node(node_type) {
}

SimpleOperand::~SimpleOperand() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
