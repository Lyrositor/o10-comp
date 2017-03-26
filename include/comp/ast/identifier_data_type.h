#pragma once

#include "comp/ast/data_type.h"
#include "comp/ast/identifier.h"
#include "comp/ast/node.h"

namespace comp {
namespace ast {
/**
 * Represents a simple named type such as `int32_t` or `void`.
 */
struct IdentifierDataType final : public DataType {
  static std::unique_ptr<IdentifierDataType> Create(
    std::shared_ptr<Identifier> identifier,
    std::shared_ptr<SourceLocation> location = nullptr);

  IdentifierDataType(
    std::shared_ptr<Identifier> identifier,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~IdentifierDataType();

  const std::shared_ptr<Identifier> identifier;
};
}  // namespace ast
}  // namespace comp
