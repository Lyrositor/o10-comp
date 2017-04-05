#include <comp/ast/binary_expression.h>

namespace comp {
namespace ast {
std::string BinaryOperatorToString(BinaryOperator op) {
  switch (op) {
    case BinaryOperator::Addition: return "Addition";
    case BinaryOperator::BitwiseAnd: return "BitwiseAnd";
    case BinaryOperator::BitwiseOr: return "BitwiseOr";
    case BinaryOperator::BitwiseXor: return "BitwiseXor";
    case BinaryOperator::Comma: return "Comma";
    case BinaryOperator::Division: return "Division";
    case BinaryOperator::Equality: return "Equality";
    case BinaryOperator::GreaterThan: return "GreaterThan";
    case BinaryOperator::GreaterThanOrEqual: return "GreaterThanOrEqual";
    case BinaryOperator::Inequality: return "Inequality";
    case BinaryOperator::LeftShift: return "LeftShift";
    case BinaryOperator::LessThan: return "LessThan";
    case BinaryOperator::LessThanOrEqualTo: return "LessThanOrEqualTo";
    case BinaryOperator::LogicalAnd: return "LogicalAnd";
    case BinaryOperator::LogicalOr: return "LogicalOr";
    case BinaryOperator::Multiplication: return "Multiplication";
    case BinaryOperator::Remainder: return "Remainder";
    case BinaryOperator::RightShift: return "RightShift";
    case BinaryOperator::Subtraction: return "Subtraction";
  }
  return "[Unknown]";
}

std::unique_ptr<BinaryExpression> BinaryExpression::Create(
  BinaryOperator op,
  std::shared_ptr<RExpression> left,
  std::shared_ptr<RExpression> right,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<BinaryExpression>(
    new BinaryExpression(op, left, right, location));
}

BinaryExpression::BinaryExpression(
  BinaryOperator op,
  std::shared_ptr<RExpression> left,
  std::shared_ptr<RExpression> right,
  std::shared_ptr<SourceLocation> location
) :
  RExpression(Type::BinaryExpression, location),
  op(op),
  left(left),
  right(right) {
}

BinaryExpression::~BinaryExpression() {
}
}  // namespace ast
}  // namespace comp
