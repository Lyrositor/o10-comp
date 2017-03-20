#pragma once

#include <memory>
#include "comp/as/ast/node.h"

namespace comp {
namespace as {
namespace ast {
/**
 * Address expression, used in directives.
 */
struct Expression : public Node {
  Expression(Type node_type);

  virtual ~Expression() = 0;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
