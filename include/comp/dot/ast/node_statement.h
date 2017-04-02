#pragma once

#include <memory>
#include <vector>
#include "comp/dot/ast/assignment.h"
#include "comp/dot/ast/statement.h"

namespace comp {
namespace dot {
namespace ast {
struct NodeStatement final : Statement {
  static std::unique_ptr<NodeStatement> Create(
    std::string id,
    std::vector<std::shared_ptr<Assignment>> attributes);

  NodeStatement(
    std::string id,
    std::vector<std::shared_ptr<Assignment>> attributes);
  ~NodeStatement();

  const std::string id;
  std::vector<std::shared_ptr<Assignment>> attributes;
};
}  // namespace ast
}  // namespace dot
}  // namespace comp
