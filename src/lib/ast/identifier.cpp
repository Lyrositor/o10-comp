#include <comp/ast/identifier.h>

namespace comp {
namespace ast {
Identifier::Identifier(std::string name, std::shared_ptr<SourceLocation> location) :
  Expression(Node::Type::Identifier, location) {
}

Identifier::~Identifier() {
}
}
}
