#pragma once

#include "node.h"
#include "data_type.h"

namespace comp {
namespace ast {
/**
 * Represents an array type such as `int ...[]`, `char ...[][]` or `int32_t ...[4]`.
 */
struct ArrayDataType final : public DataType {
  static std::unique_ptr<ArrayDataType> Create(
    std::shared_ptr<DataType> itemType,
    std::shared_ptr<SourceLocation> location = nullptr
  );

  ArrayDataType(std::shared_ptr<DataType> itemType, std::shared_ptr<SourceLocation> location = nullptr);

  ~ArrayDataType();

  // To only allow uni-dimensional arrays, replace DataType with LiteralDataType
  const std::shared_ptr<DataType> itemType;
  // TODO: handle fixed size and open size
};
}
}
