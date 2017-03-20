#include <comp/as/ast/binary_expression.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<BinaryExpression> BinaryExpression::Create(
  BinaryOperator op,
  std::shared_ptr<Expression> left,
  std::shared_ptr<Expression> right) {
  return std::unique_ptr<BinaryExpression>(new BinaryExpression(op, left, right));
}

BinaryExpression::BinaryExpression(
  BinaryOperator op,
  std::shared_ptr<Expression> left,
  std::shared_ptr<Expression> right
) :
  Expression(Type::BinaryExpression),
  op(op),
  left(left),
  right(right) {
}

BinaryExpression::~BinaryExpression() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
