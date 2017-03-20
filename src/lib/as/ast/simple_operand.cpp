#include <comp/as/ast/simple_operand.h>

namespace comp {
namespace as {
namespace ast {
SimpleOperand::SimpleOperand(
  Type node_type
) :
  Operand(node_type) {
}

SimpleOperand::~SimpleOperand() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
