#include <comp/ast/unary_expression.h>

namespace comp {
namespace ast {
std::unique_ptr<UnaryExpression> UnaryExpression::Create(
  UnaryOperator op,
  std::shared_ptr<RExpression> expression,
  std::shared_ptr<SourceLocation> location) {
  return std::unique_ptr<UnaryExpression>(
    new UnaryExpression(op, expression, location));
}

UnaryExpression::UnaryExpression(
  UnaryOperator op,
  std::shared_ptr<RExpression> expression,
  std::shared_ptr<SourceLocation> location
) :
  RExpression(Type::UnaryExpression, location),
  op(op),
  expression(expression) {
}

UnaryExpression::~UnaryExpression() {
}
}  // namespace ast
}  // namespace comp
