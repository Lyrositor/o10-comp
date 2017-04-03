#pragma once

#include <memory>
#include <string>

#include "comp/as/ast/address_expression.h"
#include "comp/as/ast/simple_operand.h"

namespace comp {
namespace as {
namespace ast {
struct AddressOperand final : public SimpleOperand {
  static std::unique_ptr<AddressOperand> Create(
    std::shared_ptr<AddressExpression> address);

  AddressOperand(std::shared_ptr<AddressExpression> address);

  ~AddressOperand();

  std::shared_ptr<AddressExpression> address;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
