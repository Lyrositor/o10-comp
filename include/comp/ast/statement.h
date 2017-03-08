#pragma once

#include "node.h"
namespace comp {
namespace ast {
struct Statement : public Node {
  Statement(Node::Type nodeType, std::shared_ptr<SourceLocation> location);

  virtual ~Statement() = 0;
};
}
}
