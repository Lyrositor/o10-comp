#include <comp/ast/literal.h>

namespace comp {
namespace ast {
Literal::Literal(int32_t value_, std::shared_ptr<SourceLocation> location_) :
    Expression(NodeType::Literal, location_), value(value_) {}
Literal::~Literal() {}

std::shared_ptr<Literal> Literal::create(int32_t value, std::shared_ptr<SourceLocation> location) {
  return std::shared_ptr<Literal>(new Literal(value, location));
}
}
}
