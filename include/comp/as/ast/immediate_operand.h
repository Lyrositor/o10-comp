#pragma once

#include <memory>
#include "comp/as/ast/simple_operand.h"

namespace comp {
namespace as {
namespace ast {
/**
 * A numeric constant directly used as an operand.
 *
 * Example:
 *
 * ```
 * $42
 * ```
 */
struct ImmediateOperand final : public SimpleOperand {
  static std::unique_ptr<ImmediateOperand> Create(int64_t value);

  ImmediateOperand(int64_t value);

  ~ImmediateOperand();

  int64_t value;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
