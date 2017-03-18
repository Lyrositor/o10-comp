#pragma once

#include "comp/ast/expression.h"

namespace comp {
namespace ast {
struct Literal : public RExpression {
  Literal(Type node_type, std::shared_ptr<SourceLocation> location);

  virtual ~Literal() = 0;
};
}  // namespace ast
}  // namespace comp
