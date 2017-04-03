#pragma once

#include <memory>
#include <vector>
#include "comp/dot/ast/node.h"
#include "comp/dot/ast/statement.h"

namespace comp {
namespace dot {
namespace ast {
struct Graph final : Node {
  static std::unique_ptr<Graph> Create(
    bool strict,
    bool directed,
    std::shared_ptr<std::string> name,
    std::vector<std::shared_ptr<Statement>> statements);

  Graph(
    bool strict,
    bool directed,
    std::shared_ptr<std::string> name,
    std::vector<std::shared_ptr<Statement>> statements);
  ~Graph();

  const bool strict;
  const bool directed;
  std::shared_ptr<std::string> name;
  std::vector<std::shared_ptr<Statement>> statements;
};
}  // namespace ast
}  // namespace dot
}  // namespace comp
