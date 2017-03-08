#include <comp/ast/expression.h>

namespace comp {
namespace ast {
Expression::Expression(Type type, std::shared_ptr<SourceLocation> location) :
  Node(type, location) {}
Expression::~Expression() {}
}
}
