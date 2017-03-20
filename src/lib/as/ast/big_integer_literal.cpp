#include <comp/as/ast/big_integer_literal.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<BigIntegerLiteral> BigIntegerLiteral::Create(int64_t value) {
  return std::unique_ptr<BigIntegerLiteral>(new BigIntegerLiteral(value));
}

BigIntegerLiteral::BigIntegerLiteral(
  int64_t value
) :
  Literal(Type::BigIntegerLiteral),
  value(value) {
}

BigIntegerLiteral::~BigIntegerLiteral() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
