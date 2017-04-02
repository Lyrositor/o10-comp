#pragma once

#include <memory>
#include <vector>
#include "comp/dot/ast/node.h"

namespace comp {
namespace dot {
namespace ast {
struct Statement : Node {
  Statement(Type node_type);
  virtual ~Statement() = 0;
};
}  // namespace ast
}  // namespace dot
}  // namespace comp
