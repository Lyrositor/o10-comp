#pragma once

#include "comp/ast/node.h"

namespace comp {
namespace ast {
struct Declarator : public Node {
  Declarator(Type node_type, std::shared_ptr<SourceLocation> location);

  ~Declarator();
};
}  // namespace ast
}  // namespace comp
