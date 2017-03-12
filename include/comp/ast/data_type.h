#pragma once

#include "node.h"

namespace comp {
namespace ast {
struct DataType : public Node {
  DataType(Node::Type nodeType, std::shared_ptr<SourceLocation> location);

  virtual ~DataType() = 0;
};
}
}
