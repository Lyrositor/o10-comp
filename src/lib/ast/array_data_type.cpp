#include <comp/ast.h>

namespace comp {
namespace ast {
std::unique_ptr<ArrayDataType> ArrayDataType::Create(
  std::shared_ptr<DataType> itemType,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<ArrayDataType>(new ArrayDataType(itemType, location));
}

ArrayDataType::ArrayDataType(
  std::shared_ptr<DataType> itemType,
  std::shared_ptr<SourceLocation> location
) :
  DataType(Node::Type::ArrayDataType, location),
  itemType(itemType) {
}

ArrayDataType::~ArrayDataType() {
}
}
}
