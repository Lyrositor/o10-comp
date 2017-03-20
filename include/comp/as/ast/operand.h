#pragma once

#include <memory>
#include "comp/as/ast/node.h"

namespace comp {
namespace as {
namespace ast {
struct Operand : public Node {
  Operand(Type node_type);

  virtual ~Operand() = 0;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
