#pragma once

#include <memory>

#include "comp/ast/statement.h"

namespace comp {
namespace ast {
struct ForStatement final : public Statement {
  static std::unique_ptr<ForStatement> Create(
    std::shared_ptr<Statement> initialization,
    std::shared_ptr<Statement> condition,
    std::shared_ptr<Statement> iteration,
    std::shared_ptr<Statement> loop,
    std::shared_ptr<SourceLocation> location = nullptr);

  ForStatement(
    std::shared_ptr<Statement> initialization,
    std::shared_ptr<Statement> condition,
    std::shared_ptr<Statement> iteration,
    std::shared_ptr<Statement> loop,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~ForStatement();

  const std::shared_ptr<Statement> initialization;
  const std::shared_ptr<Statement> condition;
  const std::shared_ptr<Statement> iteration;
  const std::shared_ptr<Statement> loop;
};
}  // namespace ast
}  // namespace comp
