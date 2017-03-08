#include <comp/ast/binary_expression.h>

namespace comp {
namespace ast {
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

BinaryExpression::~BinaryExpression() {}

std::shared_ptr<BinaryExpression> BinaryExpression::create(
    BinaryOperator op,
    std::shared_ptr<Expression> left,
    std::shared_ptr<Expression> right,
    std::shared_ptr<SourceLocation> location
) {
  return std::shared_ptr<BinaryExpression>(new BinaryExpression(op, left, right, location));
}
}
}
