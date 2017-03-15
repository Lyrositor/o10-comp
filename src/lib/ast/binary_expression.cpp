#include <comp/ast/binary_expression.h>

namespace comp {
namespace ast {
std::unique_ptr<BinaryExpression> BinaryExpression::Create(
  BinaryOperator op,
  std::shared_ptr<Expression> left,
  std::shared_ptr<Expression> right,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<BinaryExpression>(new BinaryExpression(op, left, right, location));
}

BinaryExpression::BinaryExpression(
  BinaryOperator op,
  std::shared_ptr<Expression> left,
  std::shared_ptr<Expression> right,
  std::shared_ptr<SourceLocation> location
) :
  Expression(Type::BinaryExpression, location),
  op(op),
  left(left),
  right(right) {
}

BinaryExpression::~BinaryExpression() {
}
}
}
