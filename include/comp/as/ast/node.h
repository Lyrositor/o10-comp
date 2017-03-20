#pragma once

#include <memory>

namespace comp {
namespace as {
namespace ast {
struct Node {
  enum class Type {
    AlignDirective,
    AscizDirective,
    CfiEndprocDirective,
    CfiStartprocDirective,
    CurrentAddress,
    GlobalDirective,
    Label,
    QuadDirective,
    SizeDirective,
    Statement,
    Section,
    TextDirective,
    TypeDirective
  };

  Node(Type node_type);
  virtual ~Node() = 0;

  const Type node_type;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
