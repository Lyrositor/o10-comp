#pragma once

#include "comp/ast/node.h"

namespace comp {
namespace ast {
struct LExpression : public Node {
  LExpression(Type node_type, std::shared_ptr<SourceLocation> location);

  virtual ~LExpression() = 0;
};

struct RExpression : public Node {
  RExpression(Type node_type, std::shared_ptr<SourceLocation> location);

  virtual ~RExpression() = 0;
};
}  // namespace ast
}  // namespace comp
