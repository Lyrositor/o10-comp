#pragma once

#include <memory>

#include "comp/ast/expression.h"
#include "comp/ast/statement.h"

namespace comp {
namespace ast {
struct WhileStatement final : public Statement {
  static std::unique_ptr<WhileStatement> Create(
    std::shared_ptr<RExpression> condition,
    std::shared_ptr<Statement> body,
    std::shared_ptr<SourceLocation> location = nullptr);

  WhileStatement(
    std::shared_ptr<RExpression> condition,
    std::shared_ptr<Statement> body,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~WhileStatement();

  const std::shared_ptr<RExpression> condition;
  const std::shared_ptr<Statement> body;
};
}  // namespace ast
}  // namespace comp
