#pragma once

#include <memory>
#include <vector>
#include "comp/dot/ast/assignment.h"
#include "comp/dot/ast/statement.h"

namespace comp {
namespace dot {
namespace ast {
struct AssignmentStatement final : Statement {
  static std::unique_ptr<AssignmentStatement> Create(
    std::shared_ptr<Assignment> assignment);

  AssignmentStatement(
    std::shared_ptr<Assignment> assignment);
  ~AssignmentStatement();

  std::shared_ptr<Assignment> assignment;
};
}  // namespace ast
}  // namespace dot
}  // namespace comp
