#pragma once

#include <memory>
#include "comp/as/ast/simple_operand.h"

namespace comp {
namespace as {
namespace ast {
struct ImmediateOperand final : public SimpleOperand {
  std::unique_ptr<ImmediateOperand> Create(int64_t value);

  ImmediateOperand(int64_t value);

  ~ImmediateOperand();

  int64_t value;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
