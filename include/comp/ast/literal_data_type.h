#pragma once

#include "node.h"
#include "identifier.h"
#include "data_type.h"

namespace comp {
namespace ast {
/**
 * Represents a simple named type such as `int32_t` or `void`.
 */
struct LiteralDataType final : public DataType {
  LiteralDataType(
    std::shared_ptr<Identifier> identifier,
    std::shared_ptr<SourceLocation> location = nullptr
  );

  virtual ~LiteralDataType();

  const std::shared_ptr<Identifier> identifier;
};
}
}
