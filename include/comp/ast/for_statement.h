#pragma once

#include <memory>

#include "comp/ast/statement.h"
#include "comp/ast/expression.h"

namespace comp {
namespace ast {
struct ForStatement final : public Statement {
  static std::unique_ptr<ForStatement> Create(
    std::shared_ptr<RExpression> initialization,
    std::shared_ptr<RExpression> condition,
    std::shared_ptr<RExpression> iteration,
    std::shared_ptr<Statement> body,
    std::shared_ptr<SourceLocation> location = nullptr);

  ForStatement(
    std::shared_ptr<RExpression> initialization,
    std::shared_ptr<RExpression> condition,
    std::shared_ptr<RExpression> iteration,
    std::shared_ptr<Statement> body,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~ForStatement();

  const std::shared_ptr<RExpression> initialization;
  const std::shared_ptr<RExpression> condition;
  const std::shared_ptr<RExpression> iteration;
  const std::shared_ptr<Statement> body;
};
}  // namespace ast
}  // namespace comp
