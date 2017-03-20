#include <comp/as/ast/expression.h>

namespace comp {
namespace as {
namespace ast {
Expression::Expression(
  Type node_type
) :
  Node(node_type) {
}

Expression::~Expression() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
