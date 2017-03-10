#include <comp/ast.h>

namespace comp {
namespace ast {
Type::Type(Node::Type nodeType, std::shared_ptr<SourceLocation> location) :
  Type(nodeType, location) {}
Expression::~Expression() {}
}
}
