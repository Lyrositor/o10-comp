#pragma once

#include "node.h"

namespace comp {
namespace ast {
struct Type : public Node {
  Type(Node::Type nodeType, std::shared_ptr<SourceLocation> location);

  virtual ~Type() = 0;
};
}
}
