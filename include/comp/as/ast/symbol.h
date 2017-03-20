#pragma once

#include <memory>
#include "comp/as/ast/expression.h"

namespace comp {
namespace as {
namespace ast {
/**
 * Most of the time it corresponds to a label
 */
struct Symbol : public Expression {
  Symbol(Type node_type);

  virtual ~Symbol() = 0;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
