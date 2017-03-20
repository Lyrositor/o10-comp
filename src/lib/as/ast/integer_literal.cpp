#include <comp/as/ast/integer_literal.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<IntegerLiteral> IntegerLiteral::Create(int32_t value) {
  return std::unique_ptr<IntegerLiteral>(new IntegerLiteral(value));
}

IntegerLiteral::IntegerLiteral(
  int32_t value
) :
  Literal(Type::IntegerLiteral),
  value(value) {
}

IntegerLiteral::~IntegerLiteral() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
