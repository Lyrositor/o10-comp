#pragma once

#include "comp/ast/node.h"

namespace comp {
namespace ast {
struct Statement : public Node {
  Statement(Type node_type, std::shared_ptr<SourceLocation> location);

  virtual ~Statement() = 0;
};
}  // namespace ast
}  // namespace comp
