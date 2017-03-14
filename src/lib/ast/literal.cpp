#include <comp/ast/literal.h>

namespace comp {
namespace ast {
Literal::Literal(Node::Type nodeType, std::shared_ptr<SourceLocation> location) :
  Expression(nodeType, location) {
}

Literal::~Literal() {
}
}
}
