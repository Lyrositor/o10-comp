#include <comp/as/ast/address_expression.h>

namespace comp {
namespace as {
namespace ast {
AddressExpression::AddressExpression(
  Type node_type
) :
  Node(node_type) {
}

AddressExpression::~AddressExpression() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
