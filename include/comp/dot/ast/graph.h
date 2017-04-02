#pragma once

#include <memory>
#include <vector>
#include "comp/dot/ast/node.h"

namespace comp {
namespace dot {
namespace ast {
struct Graph final : Node {
  static std::unique_ptr<Graph> Create(
    bool strict,
    bool directed,
    std::shared_ptr<std::string> name,
    std::vector<std::shared_ptr<std::string>> statements);

  Graph(
    bool strict,
    bool directed,
    std::shared_ptr<std::string> name,
    std::vector<std::shared_ptr<std::string>> statements);
  ~Graph();

  const bool strict;
  const bool directed;
  std::shared_ptr<std::string> name;
  std::vector<std::shared_ptr<std::string>> statements;
};
}  // namespace ast
}  // namespace dot
}  // namespace comp
