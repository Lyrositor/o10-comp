#pragma once

#include <memory>

#include "comp/ast/expression.h"
#include "comp/ast/statement.h"

namespace comp {
namespace ast {
/**
 * Represents a conditional `if` statement.
 * If there is no alternative ("else" branch), then `alternative` is the `nullptr`.
 */
struct IfStatement final : public Statement {
  static std::unique_ptr<IfStatement> Create(
    std::shared_ptr<RExpression> test,
    std::shared_ptr<Statement> consequence,
    std::shared_ptr<Statement> alternative,
    std::shared_ptr<SourceLocation> location = nullptr);

  IfStatement(
    std::shared_ptr<RExpression> test,
    std::shared_ptr<Statement> consequence,
    std::shared_ptr<Statement> alternative,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~IfStatement();

  const std::shared_ptr<RExpression> test;
  const std::shared_ptr<Statement> consequence;
  const std::shared_ptr<Statement> alternative;
};
}  // namespace ast
}  // namespace comp
