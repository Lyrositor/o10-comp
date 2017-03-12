#include <comp/ast.h>

namespace comp {
namespace ast {
ArrayDataType::ArrayDataType(std::shared_ptr<Type> itemType, std::shared_ptr<SourceLocation> location) :
  DataType(Node::Type::ArrayType, location), itemType(itemType) {}
ArrayDataType::~ArrayDataType() {}
}
}
