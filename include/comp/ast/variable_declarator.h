#pragma once

#include "comp/ast/declarator.h"
#include "comp/ast/expression.h"
#include "comp/ast/identifier.h"
#include "comp/ast/node.h"

namespace comp {
namespace ast {
struct VariableDeclarator final : public Node {
  static std::unique_ptr<VariableDeclarator> Create(
    std::shared_ptr<Declarator> declarator,
    std::shared_ptr<RExpression> initial_value,
    std::shared_ptr<SourceLocation> location = nullptr);

  VariableDeclarator(
    std::shared_ptr<Declarator> declarator,
    std::shared_ptr<RExpression> initial_value,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~VariableDeclarator();

  const std::shared_ptr<Declarator> declarator;
  const std::shared_ptr<RExpression> initial_value;
};
}  // namespace ast
}  // namespace comp
