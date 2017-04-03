#pragma once

#include <memory>
#include <vector>
#include "comp/dot/ast/assignment.h"
#include "comp/dot/ast/statement.h"

namespace comp {
namespace dot {
namespace ast {
struct SubgraphStatement final : Statement {
  static std::unique_ptr<SubgraphStatement> Create(
    std::shared_ptr<std::string> name,
    std::vector<std::shared_ptr<Statement>> statements);

  SubgraphStatement(
    std::shared_ptr<std::string> name,
    std::vector<std::shared_ptr<Statement>> statements);
  ~SubgraphStatement();

  std::shared_ptr<std::string> name;
  std::vector<std::shared_ptr<Statement>> statements;
};
}  // namespace ast
}  // namespace dot
}  // namespace comp
