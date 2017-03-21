#include <comp/ast/to_json.h>

namespace comp {
namespace ast {
/**
 * Creates a new empty JSON object.
 * @return A new empty JSON object
 */
std::unique_ptr<rapidjson::Document> create_object() {
  std::unique_ptr<rapidjson::Document> result(new rapidjson::Document());
  result->SetObject();
  return result;
}

std::unique_ptr<rapidjson::Document> ArrayDataTypeToJson(const ArrayDataType &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> ArrayDeclaratorToJson(const ArrayDeclarator &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> AssignmentExpressionToJson(const AssignmentExpression &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> BinaryExpressionToJson(const BinaryExpression &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> BlockStatementToJson(const BlockStatement &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> CallExpressionToJson(const CallExpression &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> DataTypeToJson(const DataType &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> DeclarationToJson(const Declaration &node) {
  switch (node.node_type) {
    case Node::Type::VariableDeclaration: {
      return VariableDeclarationToJson(static_cast<const VariableDeclaration &>(node));
    }
    default: {
      throw std::domain_error("Unexpected value for `node.node_type`");
    }
  }
}
std::unique_ptr<rapidjson::Document> ExpressionStatementToJson(const ExpressionStatement &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> ForStatementToJson(const ForStatement &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> FunctionToJson(const Function &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> IdentifierToJson(const Identifier &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> IdentifierDeclaratorToJson(const IdentifierDeclarator &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> IfStatementToJson(const IfStatement &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> Int64LiteralToJson(const Int64Literal &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> LExpressionToJson(const LExpression &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> LiteralToJson(const Literal &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> LiteralDataTypeToJson(const LiteralDataType &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> NodeToJson(const Node &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> NullStatementToJson(const NullStatement &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> ParameterToJson(const Parameter &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> PositionToJson(const Position &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> ProgramToJson(const Program &node) {
  std::unique_ptr<rapidjson::Document> result = create_object();
  result->AddMember("node_type", "Program", result->GetAllocator());
  rapidjson::Value body = rapidjson::Value();
  body.SetArray();
  for (auto declaration : node.body) {
    body.PushBack(*DeclarationToJson(*declaration), result->GetAllocator());
  }
  result->AddMember("body", body, result->GetAllocator());
  return result;
}
std::unique_ptr<rapidjson::Document> RExpressionToJson(const RExpression &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> ReturnStatementToJson(const ReturnStatement &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> StatementToJson(const Statement &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> SubscriptExpressionToJson(const SubscriptExpression &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> Uint8LiteralToJson(const Uint8Literal &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> UnaryExpressionToJson(const UnaryExpression &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> VariableDeclarationToJson(const VariableDeclaration &node) {
  std::unique_ptr<rapidjson::Document> result = create_object();
  result->AddMember("node_type", "VariableDeclaration", result->GetAllocator());
  return result;
}
std::unique_ptr<rapidjson::Document> VariableDeclaratorToJson(const VariableDeclarator &node) {
  return std::unique_ptr<rapidjson::Document>();
}
std::unique_ptr<rapidjson::Document> WhileStatementToJson(const WhileStatement &node) {
  return std::unique_ptr<rapidjson::Document>();
}
}  // namespace ast
}  // namespace comp
