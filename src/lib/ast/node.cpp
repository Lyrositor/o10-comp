#include <comp/ast/node.h>

#include <comp/utils/exceptions.h>

namespace comp {
namespace ast {
Node::Node(Type node_type, std::shared_ptr<SourceLocation> location) :
  node_type(node_type), location(location) {
}

std::string Node::ToString(Type type) {
  switch (type) {
    case Type::AnonymousParameter: return "AnonymousParameter";
    case Type::ArrayDataType: return "ArrayDataType";
    case Type::ArrayDeclarator: return "ArrayDeclarator";
    case Type::AssignmentExpression: return "AssignmentExpression";
    case Type::BinaryExpression: return "BinaryExpression";
    case Type::BlockStatement: return "BlockStatement";
    case Type::CallExpression: return "CallExpression";
    case Type::ConditionalExpression: return "ConditionalExpression";
    case Type::DeclarationForInitializer: return "DeclarationForInitializer";
    case Type::ExpressionForInitializer: return "ExpressionForInitializer";
    case Type::ExpressionStatement: return "ExpressionStatement";
    case Type::ForStatement: return "ForStatement";
    case Type::Function: return "Function";
    case Type::Identifier: return "Identifier";
    case Type::IdentifierDataType: return "IdentifierDataType";
    case Type::IdentifierDeclarator: return "IdentifierDeclarator";
    case Type::IfStatement: return "IfStatement";
    case Type::Int64Literal: return "Int64Literal";
    case Type::LogicalExpression: return "LogicalExpression";
    case Type::NullStatement: return "NullStatement";
    case Type::NamedParameter: return "NamedParameter";
    case Type::Program: return "Program";
    case Type::ReturnStatement: return "ReturnStatement";
    case Type::SubscriptExpression: return "SubscriptExpression";
    case Type::Uint8Literal: return "Uint8Literal";
    case Type::UnaryExpression: return "UnaryExpression";
    case Type::VariableDeclaration: return "VariableDeclaration";
    case Type::VariableDeclarator: return "VariableDeclarator";
    case Type::WhileStatement: return "WhileStatement";
  }
  throw Exception("unexpected ast node type");
}

Node::~Node() {
}
}  // namespace ast
}  // namespace comp
