#pragma once

#include "node.h"

namespace comp {
namespace ast {
struct Expression : public Node {
  Expression(Node::Type nodeType, std::shared_ptr<SourceLocation> location);

  virtual ~Expression() = 0;
};
}
}
