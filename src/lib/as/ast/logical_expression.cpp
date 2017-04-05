#include <comp/as/ast/logical_expression.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<LogicalExpression> LogicalExpression::Create(
  LogicalOperator op,
  std::shared_ptr<AddressExpression> left,
  std::shared_ptr<AddressExpression> right) {
  return std::unique_ptr<LogicalExpression>(new LogicalExpression(op, left, right));
}

LogicalExpression::LogicalExpression(
  LogicalOperator op,
  std::shared_ptr<AddressExpression> left,
  std::shared_ptr<AddressExpression> right
) :
  AddressExpression(Type::LogicalExpression),
  op(op),
  left(left),
  right(right) {
}

LogicalExpression::~LogicalExpression() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
