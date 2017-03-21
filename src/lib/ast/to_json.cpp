#include <comp/ast/to_json.h>

namespace comp {
namespace ast {
/**
 * Creates a new empty JSON object.
 * @return A new empty JSON object
 */
std::unique_ptr<rapidjson::Document> create_object_document() {
  std::unique_ptr<rapidjson::Document> result(new rapidjson::Document());
  result->SetObject();
  return result;
}

std::unique_ptr<rapidjson::Value> create_object_value() {
  std::unique_ptr<rapidjson::Value> result(new rapidjson::Value());
  result->SetObject();
  return result;
}

std::unique_ptr<rapidjson::Value> ArrayDataTypeToJson(const ArrayDataType &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}
std::unique_ptr<rapidjson::Value> ArrayDeclaratorToJson(const ArrayDeclarator &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}
std::unique_ptr<rapidjson::Value> AssignmentExpressionToJson(const AssignmentExpression &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}
std::unique_ptr<rapidjson::Value> BinaryExpressionToJson(const BinaryExpression &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}
std::unique_ptr<rapidjson::Value> BlockStatementToJson(const BlockStatement &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "BlockStatement", allocator);
  rapidjson::Value body = rapidjson::Value();
  body.SetArray();
  for (auto statement : node.body) {
    body.PushBack(*StatementToJson(*statement, allocator), allocator);
  }
  result->AddMember("body", body, allocator);
  return result;
}
std::unique_ptr<rapidjson::Value> CallExpressionToJson(const CallExpression &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}
std::unique_ptr<rapidjson::Value> DataTypeToJson(const DataType &node, rapidjson::Document::AllocatorType &allocator) {
  return NodeToJson(node, allocator);
}

std::unique_ptr<rapidjson::Value> DeclarationToJson(const Declaration &node, rapidjson::Document::AllocatorType &allocator) {
  switch (node.node_type) {
    case Node::Type::Function: {
      return FunctionToJson(static_cast<const Function &>(node), allocator);
    }
    case Node::Type::VariableDeclaration: {
      return VariableDeclarationToJson(static_cast<const VariableDeclaration &>(node), allocator);
    }
    default: {
      throw std::domain_error("Unexpected value for `node.node_type`");
    }
  }
}

std::unique_ptr<rapidjson::Value> ExpressionStatementToJson(const ExpressionStatement &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}

std::unique_ptr<rapidjson::Value> ForStatementToJson(const ForStatement &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}

std::unique_ptr<rapidjson::Value> FunctionToJson(const Function &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "Function", allocator);
  result->AddMember("return_type", *DataTypeToJson(*node.return_type, allocator), allocator);
  rapidjson::Value parameters = rapidjson::Value();
  parameters.SetArray();
  for (auto parameter : node.parameters) {
    parameters.PushBack(*ParameterToJson(*parameter, allocator), allocator);
  }
  result->AddMember("parameters", parameters, allocator);
  result->AddMember("body", *BlockStatementToJson(*node.body, allocator), allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> IdentifierToJson(const Identifier &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "Identifier", allocator);
  rapidjson::Value name;
  name.SetString(node.name.c_str(), allocator);
  result->AddMember("name", name, allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> IdentifierDeclaratorToJson(const IdentifierDeclarator &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}

std::unique_ptr<rapidjson::Value> IfStatementToJson(const IfStatement &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}

std::unique_ptr<rapidjson::Value> Int64LiteralToJson(const Int64Literal &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "Int64Literal", allocator);
  result->AddMember("value", node.value, allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> LExpressionToJson(const LExpression &node, rapidjson::Document::AllocatorType &allocator) {
  return NodeToJson(node, allocator);
}

std::unique_ptr<rapidjson::Value> LiteralToJson(const Literal &node, rapidjson::Document::AllocatorType &allocator) {
  return NodeToJson(node, allocator);
}

std::unique_ptr<rapidjson::Value> LiteralDataTypeToJson(const LiteralDataType &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "LiteralDataType", allocator);
  result->AddMember("identifier", *IdentifierToJson(*node.identifier, allocator), allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> NodeToJson(const Node &node, rapidjson::Document::AllocatorType &allocator) {
  switch (node.node_type) {
    case Node::Type::ArrayDataType: {
      return ArrayDataTypeToJson(static_cast<const ArrayDataType &>(node), allocator);
    }
    case Node::Type::ArrayDeclarator: {
      return ArrayDeclaratorToJson(static_cast<const ArrayDeclarator &>(node), allocator);
    }
    case Node::Type::AssignmentExpression: {
      return AssignmentExpressionToJson(static_cast<const AssignmentExpression &>(node), allocator);
    }
    case Node::Type::BinaryExpression: {
      return BinaryExpressionToJson(static_cast<const BinaryExpression &>(node), allocator);
    }
    case Node::Type::BlockStatement: {
      return BlockStatementToJson(static_cast<const BlockStatement &>(node), allocator);
    }
    case Node::Type::CallExpression: {
      return CallExpressionToJson(static_cast<const CallExpression &>(node), allocator);
    }
    case Node::Type::ExpressionStatement: {
      return ExpressionStatementToJson(static_cast<const ExpressionStatement &>(node), allocator);
    }
    case Node::Type::ForStatement: {
      return ForStatementToJson(static_cast<const ForStatement &>(node), allocator);
    }
    case Node::Type::Function: {
      return FunctionToJson(static_cast<const Function &>(node), allocator);
    }
    case Node::Type::Identifier: {
      return IdentifierToJson(static_cast<const Identifier &>(node), allocator);
    }
    case Node::Type::IdentifierDeclarator: {
      return IdentifierDeclaratorToJson(static_cast<const IdentifierDeclarator &>(node), allocator);
    }
    case Node::Type::IfStatement: {
      return IfStatementToJson(static_cast<const IfStatement &>(node), allocator);
    }
    case Node::Type::Int64Literal: {
      return Int64LiteralToJson(static_cast<const Int64Literal &>(node), allocator);
    }
    case Node::Type::LiteralDataType: {
      return LiteralDataTypeToJson(static_cast<const LiteralDataType &>(node), allocator);
    }
    case Node::Type::NullStatement: {
      return NullStatementToJson(static_cast<const NullStatement &>(node), allocator);
    }
    case Node::Type::Parameter: {
      return ParameterToJson(static_cast<const Parameter &>(node), allocator);
    }
//    case Node::Type::Program: {
//      return ProgramToJson(static_cast<const Program &>(node), allocator);
//    }
    case Node::Type::ReturnStatement: {
      return ReturnStatementToJson(static_cast<const ReturnStatement &>(node), allocator);
    }
    case Node::Type::SubscriptExpression: {
      return SubscriptExpressionToJson(static_cast<const SubscriptExpression &>(node), allocator);
    }
    case Node::Type::Uint8Literal: {
      return Uint8LiteralToJson(static_cast<const Uint8Literal &>(node), allocator);
    }
    case Node::Type::UnaryExpression: {
      return UnaryExpressionToJson(static_cast<const UnaryExpression &>(node), allocator);
    }
    case Node::Type::VariableDeclaration: {
      return VariableDeclarationToJson(static_cast<const VariableDeclaration &>(node), allocator);
    }
    case Node::Type::VariableDeclarator: {
      return VariableDeclaratorToJson(static_cast<const VariableDeclarator &>(node), allocator);
    }
    case Node::Type::WhileStatement: {
      return WhileStatementToJson(static_cast<const WhileStatement &>(node), allocator);
    }
    default: {
      throw std::domain_error("Unexpected value for `node.node_type`");
    }
  }
}

std::unique_ptr<rapidjson::Value> NullStatementToJson(const NullStatement &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}

std::unique_ptr<rapidjson::Value> ParameterToJson(const Parameter &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}

std::unique_ptr<rapidjson::Value> PositionToJson(const Position &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}

std::unique_ptr<rapidjson::Document> ProgramToJson(const Program &node) {
  std::unique_ptr<rapidjson::Document> result = create_object_document();
  rapidjson::Document::AllocatorType &allocator = result->GetAllocator();
  result->AddMember("node_type", "Program", allocator);
  rapidjson::Value body = rapidjson::Value();
  body.SetArray();
  for (auto declaration : node.body) {
    body.PushBack(*DeclarationToJson(*declaration, allocator), allocator);
  }
  result->AddMember("body", body, allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> RExpressionToJson(const RExpression &node, rapidjson::Document::AllocatorType &allocator) {
  return NodeToJson(node, allocator);
}

std::unique_ptr<rapidjson::Value> ReturnStatementToJson(const ReturnStatement &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}

std::unique_ptr<rapidjson::Value> StatementToJson(const Statement &node, rapidjson::Document::AllocatorType &allocator) {
  return NodeToJson(node, allocator);
}

std::unique_ptr<rapidjson::Value> SubscriptExpressionToJson(const SubscriptExpression &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}

std::unique_ptr<rapidjson::Value> Uint8LiteralToJson(const Uint8Literal &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}

std::unique_ptr<rapidjson::Value> UnaryExpressionToJson(const UnaryExpression &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}

std::unique_ptr<rapidjson::Value> VariableDeclarationToJson(const VariableDeclaration &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "VariableDeclaration", allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> VariableDeclaratorToJson(const VariableDeclarator &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}

std::unique_ptr<rapidjson::Value> WhileStatementToJson(const WhileStatement &node, rapidjson::Document::AllocatorType &allocator) {
  return std::unique_ptr<rapidjson::Value>();
}
}  // namespace ast
}  // namespace comp
