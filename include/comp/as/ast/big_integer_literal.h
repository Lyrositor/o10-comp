#pragma once

#include <memory>
#include "comp/as/ast/literal.h"

namespace comp {
namespace as {
namespace ast {
struct BigIntegerLiteral final : public Literal {
  static std::unique_ptr<BigIntegerLiteral> Create(int64_t value);

  BigIntegerLiteral(int64_t value);

  ~BigIntegerLiteral();

  // TODO: Use a proper big integer type
  int64_t value;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
