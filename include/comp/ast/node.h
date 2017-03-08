#pragma once

#include <cstddef>
#include <memory>
#include "position.h"

namespace comp {
namespace ast {
struct Node {
  enum class Type {
    BinaryExpression,
    ArrayExpression,
    Literal
  };

  Node(Type type, std::shared_ptr<SourceLocation> location);
  virtual ~Node() = 0;

  const Type type;
  const std::shared_ptr<SourceLocation> location;
};
}
}
