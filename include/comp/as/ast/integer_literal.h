#pragma once

#include <memory>
#include "comp/as/ast/literal.h"

namespace comp {
namespace as {
namespace ast {
struct IntegerLiteral : public Literal {
  static std::unique_ptr<IntegerLiteral> Create(int32_t value);

  IntegerLiteral(int32_t value);

  ~IntegerLiteral();

  int32_t value;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
