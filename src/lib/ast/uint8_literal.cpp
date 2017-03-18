#include <comp/ast/uint8_literal.h>

namespace comp {
namespace ast {
std::unique_ptr<Uint8Literal> Uint8Literal::Create(
  uint8_t value, std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<Uint8Literal>(new Uint8Literal(value, location));
}

Uint8Literal::Uint8Literal(
  uint8_t value,
  std::shared_ptr<SourceLocation> location
) : Literal(Type::Uint8Literal, location), value(value) {
}

Uint8Literal::~Uint8Literal() {
}
}  // namespace ast
}  // namespace comp
