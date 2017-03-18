#pragma once

#include "comp/ast/node.h"

namespace comp {
namespace ast {
struct DataType : public Node {
  DataType(Type node_type, std::shared_ptr<SourceLocation> location);

  virtual ~DataType() = 0;
};
}  // namespace ast
}  // namespace comp
