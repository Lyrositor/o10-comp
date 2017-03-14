#include <comp/ast/declaration.h>

namespace comp {
namespace ast {
Declaration::Declaration(Node::Type nodeType, std::shared_ptr<SourceLocation> location) :
  Statement(nodeType, location) {
}

Declaration::~Declaration() {
}
}
}
