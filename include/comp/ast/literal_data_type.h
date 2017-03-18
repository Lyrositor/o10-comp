#pragma once

#include "comp/ast/data_type.h"
#include "comp/ast/identifier.h"
#include "comp/ast/node.h"

namespace comp {
namespace ast {
/**
 * Represents a simple named type such as `int32_t` or `void`.
 */
struct LiteralDataType final : public DataType {
  static std::unique_ptr<LiteralDataType> Create(
    std::shared_ptr<Identifier> identifier,
    std::shared_ptr<SourceLocation> location = nullptr);

  LiteralDataType(
    std::shared_ptr<Identifier> identifier,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~LiteralDataType();

  const std::shared_ptr<Identifier> identifier;
};
}  // namespace ast
}  // namespace comp
