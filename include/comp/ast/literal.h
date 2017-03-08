#pragma once

#include "expression.h"

namespace comp {
namespace ast {
struct Literal : public Expression {
  static std::shared_ptr<Literal> create(
    int32_t value,
    std::shared_ptr<SourceLocation> location
  );

  Literal(int32_t value, std::shared_ptr<SourceLocation> location);

  virtual ~Literal();

  const int32_t value;
};
}
}
