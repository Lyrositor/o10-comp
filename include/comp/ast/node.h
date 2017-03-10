#pragma once

#include <cstddef>
#include <memory>
#include "position.h"

namespace comp {
namespace ast {
struct Node {
  enum class Type {
    ArrayType,
    BinaryExpression,
    BlockStatement,
    ExpressionStatement,
    Function,
    Identifier,
    IfStatement,
    Literal,
    LiteralType,
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
