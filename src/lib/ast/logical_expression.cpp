#include <comp/ast/logical_expression.h>

namespace comp {
namespace ast {
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