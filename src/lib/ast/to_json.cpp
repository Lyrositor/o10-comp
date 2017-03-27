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

std::unique_ptr<rapidjson::Value> AnonymousParameterToJson(const AnonymousParameter &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "AnonymousParameter", allocator);
  result->AddMember("data_type", *DataTypeToJson(*node.data_type, allocator), allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> ArrayDataTypeToJson(const ArrayDataType &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "ArrayDataType", allocator);
  result->AddMember("item_type", *DataTypeToJson(*node.item_type, allocator), allocator);
  rapidjson::Value size;
  if (node.size == nullptr) {
    size.SetNull();
  } else {
    size = *RExpressionToJson(*node.size, allocator);
  }
  result->AddMember("size", size, allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> ArrayDeclaratorToJson(const ArrayDeclarator &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "ArrayDeclarator", allocator);
  rapidjson::Value size;
  if (node.size == nullptr) {
    size.SetNull();
  } else {
    size = *RExpressionToJson(*node.size, allocator);
  }
  result->AddMember("size", size, allocator);
  return result;
}

std::string serialializeAssignmentOperator(const AssignmentOperator op) {
  switch (op) {
    case AssignmentOperator::Addition: return "+=";
    case AssignmentOperator::BitwiseAnd: return "&=";
    case AssignmentOperator::BitwiseOr: return "|=";
    case AssignmentOperator::BitwiseXor: return "^=";
    case AssignmentOperator::Division: return "/=";
    case AssignmentOperator::LeftShift: return "<<=";
    case AssignmentOperator::Multiplication: return "*=";
    case AssignmentOperator::Remainder: return "%=";
    case AssignmentOperator::RightShift: return ">>=";
    case AssignmentOperator::Simple: return "=";
    case AssignmentOperator::Subtraction: return "-=";
    default: {
      throw std::domain_error("Unexpected value for `op`");
    }
  }
}

std::unique_ptr<rapidjson::Value> AssignmentExpressionToJson(const AssignmentExpression &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "AssignmentExpression", allocator);
  rapidjson::Value op;
  op.SetString(serialializeAssignmentOperator(node.op).c_str(), allocator);
  result->AddMember("op", op, allocator);
  result->AddMember("lvalue", *LExpressionToJson(*node.lvalue, allocator), allocator);
  result->AddMember("rvalue", *RExpressionToJson(*node.rvalue, allocator), allocator);
  return result;
}

std::string serialializeBinaryOperator(const BinaryOperator op) {
  switch (op) {
    case BinaryOperator::Addition: return "+";
    case BinaryOperator::BitwiseAnd: return "&";
    case BinaryOperator::BitwiseOr: return "|";
    case BinaryOperator::BitwiseXor: return "^";
    case BinaryOperator::Comma: return ",";
    case BinaryOperator::Division: return "/";
    case BinaryOperator::Equality: return "==";
    case BinaryOperator::GreaterThan: return ">";
    case BinaryOperator::GreaterThanOrEqual: return ">=";
    case BinaryOperator::Inequality: return "!=";
    case BinaryOperator::LeftShift: return "<<";
    case BinaryOperator::LessThan: return "<";
    case BinaryOperator::LessThanOrEqualTo: return "<=";
    case BinaryOperator::LogicalAnd: return "&&";
    case BinaryOperator::LogicalOr: return "||";
    case BinaryOperator::Multiplication: return "*";
    case BinaryOperator::Remainder: return "%";
    case BinaryOperator::RightShift: return ">>";
    case BinaryOperator::Subtraction: return "-";
    default: {
      throw std::domain_error("Unexpected value for `op`");
    }
  }
}

std::unique_ptr<rapidjson::Value> BinaryExpressionToJson(const BinaryExpression &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "BinaryExpression", allocator);
  rapidjson::Value op;
  op.SetString(serialializeBinaryOperator(node.op).c_str(), allocator);
  result->AddMember("op", op, allocator);
  result->AddMember("left", *RExpressionToJson(*node.left, allocator), allocator);
  result->AddMember("right", *RExpressionToJson(*node.right, allocator), allocator);
  return result;
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
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "CallExpression", allocator);
  result->AddMember("callee", *RExpressionToJson(*node.callee, allocator), allocator);
  rapidjson::Value arguments = rapidjson::Value();
  arguments.SetArray();
  for (auto argument : node.arguments) {
    arguments.PushBack(*RExpressionToJson(*argument, allocator), allocator);
  }
  result->AddMember("arguments", arguments, allocator);
  return result;
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

std::unique_ptr<rapidjson::Value> DeclaratorToJson(const Declarator &node, rapidjson::Document::AllocatorType &allocator) {
  return NodeToJson(node, allocator);
}

std::unique_ptr<rapidjson::Value> ExpressionStatementToJson(const ExpressionStatement &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "ExpressionStatement", allocator);
  result->AddMember("expression", *RExpressionToJson(*node.expression, allocator), allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> ForStatementToJson(const ForStatement &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "ForStatement", allocator);
  result->AddMember("initialization", *RExpressionToJson(*node.initialization, allocator), allocator);
  result->AddMember("condition", *RExpressionToJson(*node.condition, allocator), allocator);
  result->AddMember("iteration", *RExpressionToJson(*node.iteration, allocator), allocator);
  result->AddMember("body", *StatementToJson(*node.body, allocator), allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> FunctionToJson(const Function &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "Function", allocator);
  result->AddMember("return_type", *DataTypeToJson(*node.return_type, allocator), allocator);
  rapidjson::Value parameters = rapidjson::Value();
  parameters.SetArray();
  for (auto parameter : node.parameters) {
    parameters.PushBack(*NodeToJson(*parameter, allocator), allocator);
  }
  result->AddMember("parameters", parameters, allocator);

  rapidjson::Value body;
  if (node.body == nullptr) {
    body.SetNull();
  } else {
    body = *BlockStatementToJson(*node.body, allocator);
  }
  result->AddMember("body", body, allocator);
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
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "IdentifierDeclarator", allocator);
  result->AddMember("identifier", *IdentifierToJson(*node.identifier, allocator), allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> IfStatementToJson(const IfStatement &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "IfStatement", allocator);
  result->AddMember("test", *RExpressionToJson(*node.test, allocator), allocator);
  result->AddMember("consequence", *StatementToJson(*node.consequence, allocator), allocator);
  rapidjson::Value alternative;
  if (node.alternative == nullptr) {
    alternative.SetNull();
  } else {
    alternative = *StatementToJson(*node.alternative, allocator);
  }
  result->AddMember("alternative", alternative, allocator);
  return result;
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

std::unique_ptr<rapidjson::Value> LiteralDataTypeToJson(const IdentifierDataType &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "IdentifierDataType", allocator);
  result->AddMember("identifier", *IdentifierToJson(*node.identifier, allocator), allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> NamedParameterToJson(const NamedParameter &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "NamedParameter", allocator);
  result->AddMember("data_type", *LiteralDataTypeToJson(*node.data_type, allocator), allocator);
  result->AddMember("declarator", *DeclaratorToJson(*node.declarator, allocator), allocator);
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
    case Node::Type::IdentifierDataType: {
      return LiteralDataTypeToJson(static_cast<const IdentifierDataType &>(node), allocator);
    }
    case Node::Type::NullStatement: {
      return NullStatementToJson(static_cast<const NullStatement &>(node), allocator);
    }
    case Node::Type::NamedParameter: {
      return NamedParameterToJson(static_cast<const NamedParameter &>(node), allocator);
    }
    case Node::Type::AnonymousParameter: {
      return AnonymousParameterToJson(static_cast<const AnonymousParameter &>(node), allocator);
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
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "NullStatementToJson", allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> PositionToJson(const Position &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("index", node.index, allocator);
  result->AddMember("line", node.line, allocator);
  result->AddMember("column", node.column, allocator);
  return result;
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
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "ReturnStatement", allocator);
  rapidjson::Value expression;
  if (node.expression == nullptr) {
    expression.SetNull();
  } else {
    expression = *RExpressionToJson(*node.expression, allocator);
  }
  result->AddMember("expression", expression, allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> StatementToJson(const Statement &node, rapidjson::Document::AllocatorType &allocator) {
  return NodeToJson(node, allocator);
}

std::unique_ptr<rapidjson::Value> SubscriptExpressionToJson(const SubscriptExpression &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "SubscriptExpression", allocator);
  result->AddMember("array", *RExpressionToJson(*node.array, allocator), allocator);
  result->AddMember("index", *RExpressionToJson(*node.index, allocator), allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> Uint8LiteralToJson(const Uint8Literal &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "Uint8Literal", allocator);
  result->AddMember("value", node.value, allocator);
  return result;
}

std::string serialializeUnaryOperator(const UnaryOperator op) {
  switch (op) {
    case UnaryOperator::Address: return "Address";
    case UnaryOperator::BitwiseComplement: return "BitwiseComplement";
    case UnaryOperator::Indirection: return "Indirection";
    case UnaryOperator::LogicalNegation: return "LogicalNegation";
    case UnaryOperator::PostfixDecrement: return "PostfixDecrement";
    case UnaryOperator::PostfixIncrement: return "PostfixIncrement";
    case UnaryOperator::PrefixDecrement: return "PrefixDecrement";
    case UnaryOperator::PrefixIncrement: return "PrefixIncrement";
    case UnaryOperator::UnaryMinus: return "UnaryMinus";
    case UnaryOperator::UnaryPlus: return "UnaryPlus";
    default: {
      throw std::domain_error("Unexpected value for `op`");
    }
  }
}

std::unique_ptr<rapidjson::Value> UnaryExpressionToJson(const UnaryExpression &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "UnaryExpression", allocator);
  rapidjson::Value op;
  op.SetString(serialializeUnaryOperator(node.op).c_str(), allocator);
  result->AddMember("op", op, allocator);
  result->AddMember("expression", *RExpressionToJson(*node.expression, allocator), allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> VariableDeclarationToJson(const VariableDeclaration &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "VariableDeclaration", allocator);
  result->AddMember("data_type",*DataTypeToJson(*node.data_type, allocator), allocator);
  rapidjson::Value declarators = rapidjson::Value();
  declarators.SetArray();
  for (auto declarator : node.declarators) {
    declarators.PushBack(*VariableDeclaratorToJson(*declarator, allocator), allocator);
  }
  result->AddMember("declarators", declarators, allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> VariableDeclaratorToJson(const VariableDeclarator &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "VariableDeclarator", allocator);
  result->AddMember("declarator", *DeclaratorToJson(*node.declarator, allocator), allocator);
  rapidjson::Value initial_value;
  if (node.initial_value == nullptr) {
    initial_value.SetNull();
  } else {
    initial_value = *RExpressionToJson(*node.initial_value, allocator);
  }
  result->AddMember("initial_value", initial_value, allocator);
  return result;
}

std::unique_ptr<rapidjson::Value> WhileStatementToJson(const WhileStatement &node, rapidjson::Document::AllocatorType &allocator) {
  std::unique_ptr<rapidjson::Value> result = create_object_value();
  result->AddMember("node_type", "WhileStatement", allocator);
  result->AddMember("condition", *RExpressionToJson(*node.condition, allocator), allocator);
  result->AddMember("body", *StatementToJson(*node.body, allocator), allocator);
  return result;
}
}  // namespace ast
}  // namespace comp
