#pragma once

#include "expression.h"

namespace comp {
namespace ast {
struct Literal : public Expression {
  Literal(Node::Type nodeType, std::shared_ptr<SourceLocation> location);

  virtual ~Literal() = 0;
};
}
}
