#pragma once

#include <memory>

#include "comp/ast/expression.h"
#include "comp/ast/statement.h"

namespace comp {
namespace ast {
struct ExpressionStatement final : public Statement {
  static std::unique_ptr<ExpressionStatement> Create(
    std::shared_ptr<RExpression> expression,
    std::shared_ptr<SourceLocation> location = nullptr);

  ExpressionStatement(
    std::shared_ptr<RExpression> expression,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~ExpressionStatement();

  const std::shared_ptr<RExpression> expression;
};
}  // namespace ast
}  // namespace comp
