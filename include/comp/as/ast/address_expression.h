#pragma once

#include <memory>
#include "comp/as/ast/node.h"

namespace comp {
namespace as {
namespace ast {
/**
 * Address expression, used in directives.
 */
struct AddressExpression : public Node {
  AddressExpression(Type node_type);

  virtual ~AddressExpression() = 0;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
