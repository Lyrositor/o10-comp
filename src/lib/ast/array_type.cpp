#include <comp/ast.h>

namespace comp {
namespace ast {
ArrayType::ArrayType(std::shared_ptr<Type> itemType, std::shared_ptr<SourceLocation> location) :
  Type(Node::Type::ArrayType, location), itemType(itemType) {}
ArrayType::~ArrayType() {}
}
}
