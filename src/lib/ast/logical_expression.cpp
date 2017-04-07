#include <comp/ast/logical_expression.h>

#include <comp/utils/exceptions.h>

namespace comp {
namespace ast {
std::string LogicalOperatorToString(LogicalOperator op) {
  switch (op) {
    case LogicalOperator::LogicalAnd: return "LogicalAnd";
    case LogicalOperator::LogicalOr: return "LogicalOr";
  }
  throw Exception("unexpected LogicalOperator type");
}

std::unique_ptr<LogicalExpression> LogicalExpression::Create(
  LogicalOperator op,
  std::shared_ptr<RExpression> left,
  std::shared_ptr<RExpression> right,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<LogicalExpression>(
    new LogicalExpression(op, left, right, location));
}

LogicalExpression::LogicalExpression(
  LogicalOperator op,
  std::shared_ptr<RExpression> left,
  std::shared_ptr<RExpression> right,
  std::shared_ptr<SourceLocation> location
) :
  RExpression(Type::LogicalExpression, location),
  op(op),
  left(left),
  right(right) {
}

LogicalExpression::~LogicalExpression() {
}
}  // namespace ast
}  // namespace comp
