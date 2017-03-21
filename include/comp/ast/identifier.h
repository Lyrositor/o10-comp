#pragma once

#include <string>

#include "comp/ast/expression.h"

namespace comp {
namespace ast {
struct Identifier final : public LExpression {
  static std::unique_ptr<Identifier> Create(
    std::string name,
    std::shared_ptr<SourceLocation> location = nullptr);

  Identifier(
    std::string name,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~Identifier();

  const std::string name;
};
}  // namespace ast
}  // namespace comp
