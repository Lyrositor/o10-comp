#include <comp/as/ast/literal.h>

namespace comp {
namespace as {
namespace ast {
Literal::Literal(
  Type node_type
) :
  AddressExpression(node_type) {
}

Literal::~Literal() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
