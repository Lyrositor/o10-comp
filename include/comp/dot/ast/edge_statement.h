#pragma once

#include <memory>
#include <vector>
#include "comp/dot/ast/assignment.h"
#include "comp/dot/ast/statement.h"

namespace comp {
namespace dot {
namespace ast {
struct EdgeStatement final : Statement {
  static std::unique_ptr<EdgeStatement> Create(
    std::vector<std::string> nodes,
    std::vector<std::shared_ptr<Assignment>> attributes);

  EdgeStatement(
    std::vector<std::string> nodes,
    std::vector<std::shared_ptr<Assignment>> attributes);
  ~EdgeStatement();

  std::vector<std::string> nodes;
  std::vector<std::shared_ptr<Assignment>> attributes;
};
}  // namespace ast
}  // namespace dot
}  // namespace comp
