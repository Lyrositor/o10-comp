#include <comp/ast.h>

namespace comp {
namespace ast {
LiteralType::LiteralType(std::shared_ptr<Identifier> identifier, std::shared_ptr<SourceLocation> location) :
  Type(Node::Type::LiteralType, location), identifier(identifier) {}
ArrayType::~ArrayType() {}
}
}
