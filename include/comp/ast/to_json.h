#pragma once

#include <memory>
#include <rapidjson/document.h>
#include "comp/ast.h"

namespace comp {
namespace ast {
std::unique_ptr<rapidjson::Value> AnonymousParameterToJson(const AnonymousParameter &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> ArrayDataTypeToJson(const ArrayDataType &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> ArrayDeclaratorToJson(const ArrayDeclarator &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> AssignmentExpressionToJson(const AssignmentExpression &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> BinaryExpressionToJson(const BinaryExpression &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> BlockStatementToJson(const BlockStatement &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> CallExpressionToJson(const CallExpression &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> DataTypeToJson(const DataType &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> DeclarationToJson(const Declaration &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> DeclaratorToJson(const Declarator &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> ExpressionStatementToJson(const ExpressionStatement &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> ForStatementToJson(const ForStatement &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> FunctionToJson(const Function &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> IdentifierToJson(const Identifier &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> IdentifierDeclaratorToJson(const IdentifierDeclarator &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> IfStatementToJson(const IfStatement &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> Int64LiteralToJson(const Int64Literal &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> LExpressionToJson(const LExpression &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> LiteralToJson(const Literal &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> LiteralDataTypeToJson(const LiteralDataType &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> NamedParameterToJson(const NamedParameter &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> NodeToJson(const Node &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> NullStatementToJson(const NullStatement &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> PositionToJson(const Position &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Document> ProgramToJson(const Program &node);
std::unique_ptr<rapidjson::Value> RExpressionToJson(const RExpression &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> ReturnStatementToJson(const ReturnStatement &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> StatementToJson(const Statement &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> SubscriptExpressionToJson(const SubscriptExpression &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> Uint8LiteralToJson(const Uint8Literal &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> UnaryExpressionToJson(const UnaryExpression &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> VariableDeclarationToJson(const VariableDeclaration &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> VariableDeclaratorToJson(const VariableDeclarator &node, rapidjson::Document::AllocatorType &allocator);
std::unique_ptr<rapidjson::Value> WhileStatementToJson(const WhileStatement &node, rapidjson::Document::AllocatorType &allocator);
}  // namespace ast
}  // namespace comp
