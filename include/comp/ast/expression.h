#pragma once

#include "comp/ast/node.h"

namespace comp {
namespace ast {
struct RExpression : public Node {
  RExpression(Type node_type, std::shared_ptr<SourceLocation> location);

  virtual ~RExpression() = 0;
};

struct LExpression : public RExpression {
  LExpression(Type node_type, std::shared_ptr<SourceLocation> location);

  virtual ~LExpression() = 0;
};
}  // namespace ast
}  // namespace comp
