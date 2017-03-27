#pragma once

#include <memory>

#include "comp/ast/position.h"

namespace comp {
namespace ast {
struct Node {
  enum class Type {
    AnonymousParameter,
    ArrayDataType,
    ArrayDeclarator,
    AssignmentExpression,
    BinaryExpression,
    BlockStatement,
    CallExpression,
    ConditionalExpression,
    ExpressionStatement,
    ForStatement,
    Function,
    Identifier,
    IdentifierDataType,
    IdentifierDeclarator,
    IfStatement,
    Int64Literal,
    NullStatement,
    NamedParameter,
    Program,
    ReturnStatement,
    SubscriptExpression,
    Uint8Literal,
    UnaryExpression,
    VariableDeclaration,
    VariableDeclarator,
    WhileStatement
  };

  Node(Type node_type, std::shared_ptr<SourceLocation> location);
  virtual ~Node() = 0;

  const Type node_type;
  const std::shared_ptr<SourceLocation> location;
};
}  // namespace ast
}  // namespace comp
