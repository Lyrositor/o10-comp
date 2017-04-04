#include <comp/ast/node.h>

namespace comp {
namespace ast {
Node::Node(Type node_type, std::shared_ptr<SourceLocation> location) :
  node_type(node_type), location(location) {
}


std::string Node::ToString(Type type){
  switch (type)
  {
    case Node::Type::AnonymousParameter:   return "AnonymousParameter";
    case Node::Type::ArrayDataType:   return "ArrayDataType";
    case Node::Type::ArrayDeclarator: return "ArrayDeclarator";
    case Node::Type::AssignmentExpression: return "AssignmentExpression";
    case Node::Type::BinaryExpression: return "BinaryExpression";
    case Node::Type::BlockStatement: return "BlockStatement";
    case Node::Type::CallExpression: return "CallExpression";
    case Node::Type::ConditionalExpression: return "ConditionalExpression";
    case Node::Type::ExpressionStatement: return "ExpressionStatement";
    case Node::Type::ForStatement: return "ForStatement";
    case Node::Type::Function: return "Function";
    case Node::Type::Identifier: return "Identifier";
    case Node::Type::IdentifierDataType: return "IdentifierDataType";
    case Node::Type::IdentifierDeclarator: return "IdentifierDeclarator";
    case Node::Type::IfStatement: return "IfStatement";
    case Node::Type::Int64Literal: return "Int64Literal";
    case Node::Type::NullStatement: return "NullStatement";
    case Node::Type::NamedParameter: return "NamedParameter";
    case Node::Type::Program: return "Program";
    case Node::Type::ReturnStatement: return "ReturnStatement";
    case Node::Type::SubscriptExpression: return "SubscriptExpression";
    case Node::Type::Uint8Literal: return "Uint8Literal";
    case Node::Type::UnaryExpression: return "UnaryExpression";
    case Node::Type::VariableDeclaration: return "VariableDeclaration";
    case Node::Type::VariableDeclarator: return "VariableDeclarator";
    case Node::Type::WhileStatement: return "WhileStatement";
    default:      return "[Unknown OS_type]";
  }
}

Node::~Node() {
}
}  // namespace ast
}  // namespace comp