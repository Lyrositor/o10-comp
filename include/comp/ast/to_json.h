#pragma once

#include <memory>
#include <rapidjson/document.h>
#include "comp/ast.h"

namespace comp {
namespace ast {
std::unique_ptr<rapidjson::Document> ArrayDataTypeToJson(const ArrayDataType &node);
std::unique_ptr<rapidjson::Document> ArrayDeclaratorToJson(const ArrayDeclarator &node);
std::unique_ptr<rapidjson::Document> AssignmentExpressionToJson(const AssignmentExpression &node);
std::unique_ptr<rapidjson::Document> BinaryExpressionToJson(const BinaryExpression &node);
std::unique_ptr<rapidjson::Document> BlockStatementToJson(const BlockStatement &node);
std::unique_ptr<rapidjson::Document> CallExpressionToJson(const CallExpression &node);
std::unique_ptr<rapidjson::Document> DataTypeToJson(const DataType &node);
std::unique_ptr<rapidjson::Document> DeclarationToJson(const Declaration &node);
std::unique_ptr<rapidjson::Document> ExpressionStatementToJson(const ExpressionStatement &node);
std::unique_ptr<rapidjson::Document> ForStatementToJson(const ForStatement &node);
std::unique_ptr<rapidjson::Document> FunctionToJson(const Function &node);
std::unique_ptr<rapidjson::Document> IdentifierToJson(const Identifier &node);
std::unique_ptr<rapidjson::Document> IdentifierDeclaratorToJson(const IdentifierDeclarator &node);
std::unique_ptr<rapidjson::Document> IfStatementToJson(const IfStatement &node);
std::unique_ptr<rapidjson::Document> Int64LiteralToJson(const Int64Literal &node);
std::unique_ptr<rapidjson::Document> LExpressionToJson(const LExpression &node);
std::unique_ptr<rapidjson::Document> LiteralToJson(const Literal &node);
std::unique_ptr<rapidjson::Document> LiteralDataTypeToJson(const LiteralDataType &node);
std::unique_ptr<rapidjson::Document> NodeToJson(const Node &node);
std::unique_ptr<rapidjson::Document> NullStatementToJson(const NullStatement &node);
std::unique_ptr<rapidjson::Document> ParameterToJson(const Parameter &node);
std::unique_ptr<rapidjson::Document> PositionToJson(const Position &node);
std::unique_ptr<rapidjson::Document> ProgramToJson(const Program &node);
std::unique_ptr<rapidjson::Document> RExpressionToJson(const RExpression &node);
std::unique_ptr<rapidjson::Document> ReturnStatementToJson(const ReturnStatement &node);
std::unique_ptr<rapidjson::Document> StatementToJson(const Statement &node);
std::unique_ptr<rapidjson::Document> SubscriptExpressionToJson(const SubscriptExpression &node);
std::unique_ptr<rapidjson::Document> Uint8LiteralToJson(const Uint8Literal &node);
std::unique_ptr<rapidjson::Document> UnaryExpressionToJson(const UnaryExpression &node);
std::unique_ptr<rapidjson::Document> VariableDeclarationToJson(const VariableDeclaration &node);
std::unique_ptr<rapidjson::Document> VariableDeclaratorToJson(const VariableDeclarator &node);
std::unique_ptr<rapidjson::Document> WhileStatementToJson(const WhileStatement &node);
}  // namespace ast
}  // namespace comp
