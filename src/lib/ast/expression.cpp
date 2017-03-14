#include <comp/ast/expression.h>

namespace comp {
namespace ast {
Expression::Expression(Node::Type nodeType, std::shared_ptr<SourceLocation> location) :
  Node(nodeType, location) {
}

Expression::~Expression() {
}
}
}
