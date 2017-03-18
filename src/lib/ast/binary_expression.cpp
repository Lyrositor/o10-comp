#include <comp/ast/binary_expression.h>

namespace comp {
namespace ast {
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
