#pragma once

#include "comp/ast/data_type.h"
#include "comp/ast/expression.h"
#include "comp/ast/node.h"

namespace comp {
namespace ast {
/**
 * Represents an array type such as `int ...[]`, `char ...[][]` or `int32_t ...[4]`.
 */
struct ArrayDataType final : public DataType {
  static std::unique_ptr<ArrayDataType> Create(
    std::shared_ptr<DataType> item_type,
    std::shared_ptr<RExpression> size,
    std::shared_ptr<SourceLocation> location = nullptr);

  ArrayDataType(
    std::shared_ptr<DataType> item_type,
    std::shared_ptr<RExpression> size,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~ArrayDataType();

  const std::shared_ptr<DataType> item_type;
  /**
   * Can be a nullptr. If size is a nullptr then it designates an array with an unknown size.
   */
  const std::shared_ptr<RExpression> size;
};
}  // namespace ast
}  // namespace comp
