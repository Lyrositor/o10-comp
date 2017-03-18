#pragma once

#include <cstddef>

#include "comp/ast/literal.h"

namespace comp {
namespace ast {
struct Uint8Literal final : public Literal {
  static std::unique_ptr<Uint8Literal> Create(
    uint8_t value,
    std::shared_ptr<SourceLocation> location = nullptr);

  Uint8Literal(uint8_t value, std::shared_ptr<SourceLocation> location);

  virtual ~Uint8Literal();

  const uint8_t value;
};
}  // namespace ast
}  // namespace comp
