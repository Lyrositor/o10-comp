#include <comp/as/ast/symbol.h>

namespace comp {
namespace as {
namespace ast {
Symbol::Symbol(
  Type node_type
) :
  Expression(node_type) {
}

Symbol::~Symbol() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
