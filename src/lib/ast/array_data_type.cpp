#include <comp/ast/array_data_type.h>

namespace comp {
namespace ast {
std::unique_ptr<ArrayDataType> ArrayDataType::Create(
  std::shared_ptr<DataType> item_type,
  std::shared_ptr<RExpression> size,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<ArrayDataType>(new ArrayDataType(item_type, size, location));
}

ArrayDataType::ArrayDataType(
  std::shared_ptr<DataType> item_type,
  std::shared_ptr<RExpression> size,
  std::shared_ptr<SourceLocation> location
) :
  DataType(Type::ArrayDataType, location),
  item_type(item_type),
  size(size) {
}

ArrayDataType::~ArrayDataType() {
}
}  // namespace ast
}  // namespace comp
