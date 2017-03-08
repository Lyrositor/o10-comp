#include <comp/ast/binary_expression.h>

namespace comp {
namespace ast {
BinaryExpression::BinaryExpression(BinaryOperator op_, std::shared_ptr<Expression> left_,
                                   std::shared_ptr<Expression> right_, std::shared_ptr<SourceLocation> location_) :
    Expression(NodeType::BinaryExpression, location_), op(op_), left(left_), right(right_) {}
BinaryExpression::~BinaryExpression() {}

std::shared_ptr<BinaryExpression> BinaryExpression::create(BinaryOperator operator_,
                                                           std::shared_ptr<Expression> left,
                                                           std::shared_ptr<Expression> right,
                                                           std::shared_ptr<SourceLocation> location) {
  return std::shared_ptr<BinaryExpression>(new BinaryExpression(operator_, left, right, location));
}
}
}
