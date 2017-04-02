#pragma once

#include <memory>

namespace comp {
namespace dot {
namespace ast {
struct Node {
  enum class Type {
    Assignment,
    AssignmentStatement,
    EdgeStatement,
    Graph,
    NodeStatement,
    SubgraphStatement
  };

  Node(Type node_type);
  virtual ~Node() = 0;

  const Type node_type;
};
}  // namespace ast
}  // namespace dot
}  // namespace comp
