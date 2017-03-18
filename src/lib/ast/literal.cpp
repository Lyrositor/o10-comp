#include <comp/ast/literal.h>

namespace comp {
namespace ast {
Literal::Literal(Type node_type, std::shared_ptr<SourceLocation> location) :
  RExpression(node_type, location) {
}

Literal::~Literal() {
}
}  // namespace ast
}  // namespace comp
