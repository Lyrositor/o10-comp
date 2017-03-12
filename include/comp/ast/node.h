#pragma once

#include <cstddef>
#include <memory>
#include "position.h"

namespace comp {
namespace ast {
struct Node {
  enum class Type {
    ArrayDataType,
    BinaryExpression,
    BlockStatement,
    ExpressionStatement,
    Function,
    Identifier,
    IfStatement,
    Int64Literal,
    LiteralDataType,
    Program,
    VariableDeclaration,
    VariableDeclarator
  };

  Node(Type nodeType, std::shared_ptr<SourceLocation> location);
  virtual ~Node() = 0;

  const Type nodeType;
  const std::shared_ptr<SourceLocation> location;
};
}
}
