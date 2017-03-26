#pragma once

#include <string>

#include "comp/ast/declarator.h"
#include "comp/ast/identifier.h"

namespace comp {
namespace ast {
struct IdentifierDeclarator final : public Declarator {
  static std::unique_ptr<IdentifierDeclarator> Create(
    std::shared_ptr<Identifier> identifier,
    std::shared_ptr<SourceLocation> location = nullptr);

  IdentifierDeclarator(
    std::shared_ptr<Identifier> identifier,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~IdentifierDeclarator();

  std::string GetName() const override;

  const std::shared_ptr<Identifier> identifier;
};
}  // namespace ast
}  // namespace comp
