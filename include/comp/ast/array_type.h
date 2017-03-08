#pragma once

#include "node.h"

namespace comp {
namespace ast {
/**
 * Represents an array type such as `int ...[]`, `char ...[][]` or `int32_t ...[4]`.
 */
struct ArrayType final : public Node {
  ArrayType(std::shared_ptr<Type> itemType, std::shared_ptr<SourceLocation> location = nullptr);

  virtual ~ArrayType();

  // To only allow uni-dimensional arrays, replace Type with LiteralType
  const std::shared_ptr<Type> itemType;
  // TODO: handle fixed size and open size
};
}
}
