#pragma once

#include <memory>
#include "comp/as/ast/node.h"

namespace comp {
namespace as {
namespace ast {
/**
 * Immediate operand & register operand
 */
struct SimpleOperand : public Node {
  SimpleOperand(Type node_type);

  virtual ~SimpleOperand() = 0;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
