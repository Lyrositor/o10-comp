#include <comp/ast/int64_literal.h>

namespace comp {
namespace ast {
Int64Literal::Int64Literal(int64_t value_, std::shared_ptr<SourceLocation> location_) :
  Literal(Node::Type::Int64Literal, location_), value(value_) {}
Int64Literal::~Int64Literal() {}

std::shared_ptr<Int64Literal> Int64Literal::create(int64_t value, std::shared_ptr<SourceLocation> location) {
  return std::shared_ptr<Int64Literal>(new Int64Literal(value, location));
}
}
}
