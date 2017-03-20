#pragma once

#include <memory>
#include "comp/as/ast/node.h"

namespace comp {
namespace as {
namespace ast {
struct Directive : public Node {
  Directive(Type node_type);

  virtual ~Directive() = 0;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
