#pragma once

#include <memory>
#include "comp/as/ast/address_expression.h"

namespace comp {
namespace as {
namespace ast {
/**
 * Most of the time it corresponds to a label
 */
struct Symbol : public AddressExpression {
  Symbol(Type node_type);

  virtual ~Symbol() = 0;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
