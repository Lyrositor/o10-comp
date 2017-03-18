#pragma once

#include "comp/ast/expression.h"
#include "comp/ast/identifier.h"
#include "comp/ast/node.h"

namespace comp {
namespace ast {
struct VariableDeclarator final : public Node {
  static std::unique_ptr<VariableDeclarator> Create(
    std::shared_ptr<Identifier> identifier,
    std::shared_ptr<RExpression> initial_value,
    std::shared_ptr<SourceLocation> location = nullptr);

  VariableDeclarator(
    std::shared_ptr<Identifier> identifier,
    std::shared_ptr<RExpression> initial_value,
    std::shared_ptr<SourceLocation> location = nullptr);
  // TODO(Lyrositor) Handle int a[], b

  ~VariableDeclarator();

  const std::shared_ptr<Identifier> identifier;
  const std::shared_ptr<RExpression> initial_value;
};
}  // namespace ast
}  // namespace comp
