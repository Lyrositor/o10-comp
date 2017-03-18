#include <comp/ast/int64_literal.h>

namespace comp {
namespace ast {
std::shared_ptr<Int64Literal> Int64Literal::Create(
  int64_t value,
  std::shared_ptr<SourceLocation> location
) {
  return std::shared_ptr<Int64Literal>(new Int64Literal(value, location));
}

Int64Literal::Int64Literal(
  int64_t value,
  std::shared_ptr<SourceLocation> location
) : Literal(Node::Type::Int64Literal, location), value(value) {
}

Int64Literal::~Int64Literal() {
}
}  // namespace ast
}  // namespace comp
