#pragma once

#include <memory>
#include "comp/as/ast/address_expression.h"

namespace comp {
namespace as {
namespace ast {
struct Literal : public AddressExpression {
  Literal(Type node_type);

  virtual ~Literal() = 0;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
