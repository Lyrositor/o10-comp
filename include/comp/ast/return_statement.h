#pragma once

#include "comp/ast/expression.h"
#include "comp/ast/statement.h"

namespace comp {
namespace ast {
struct ReturnStatement final : public Statement {
  static std::unique_ptr<ReturnStatement> Create(
    std::shared_ptr<RExpression> expression,
    std::shared_ptr<SourceLocation> location = nullptr);

  ReturnStatement(
    std::shared_ptr<RExpression> expression,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~ReturnStatement();

  const std::shared_ptr<RExpression> expression;
};
}  // namespace ast
}  // namespace comp
