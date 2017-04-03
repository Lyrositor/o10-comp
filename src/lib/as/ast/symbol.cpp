#include <comp/as/ast/symbol.h>

namespace comp {
namespace as {
namespace ast {
Symbol::Symbol(
  Type node_type
) :
  AddressExpression(node_type) {
}

Symbol::~Symbol() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
