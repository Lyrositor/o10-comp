#pragma once

#include "node.h"
#include "identifier.h"
#include "type.h"

namespace comp {
namespace ast {
/**
 * Represents a simple named type such as `int32_t` or `void`.
 */
struct LiteralType final : public Type {
  LiteralType(
    std::shared_ptr<Identifier> literal,
    std::shared_ptr<SourceLocation> location = nullptr
  );

  virtual ~LiteralType();

  const std::shared_ptr<Identifier> literal;
};
}
}
