#pragma once

#include <memory>
#include "comp/as/ast/directive.h"
#include "comp/as/ast/address_expression.h"

namespace comp {
namespace as {
namespace ast {
/**
 * @see: https://sourceware.org/binutils/docs/as/Dot.html#Dot
 */
struct CurrentAddress final : public AddressExpression {
  static std::unique_ptr<CurrentAddress> Create();

  CurrentAddress();

  ~CurrentAddress();
};
}  // namespace ast
}  // namespace as
}  // namespace comp
