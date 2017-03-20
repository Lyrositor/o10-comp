#pragma once

#include <memory>
#include "comp/as/ast/expression.h"

namespace comp {
namespace as {
namespace ast {
enum class BinaryOperator {
  Addition, // left + right
  BitwiseAnd, // left & right
  BitwiseOr, // left | right
  BitwiseOrNot, // left ! right
  BitwiseXor, // left ^ right
  Division, // left / right
  Equal, // left == right
  GreaterThan, // left > right
  GreaterThanOrEqual, // left >= right
  LessThan, // left < right
  LessThanOrEqual, // left <= right
  LogicalAnd, // left && right
  LogicalOr, // left || right
  Multiplication, // left * right
  NotEqual, // left != right
  Remainder, // left % right
  ShiftLeft, // left << right
  ShiftRight, // left >> right
  Subtraction // left - right
};

struct BinaryExpression final : public Expression {
  static std::unique_ptr<BinaryExpression> Create(
    BinaryOperator op,
    std::shared_ptr<Expression> left,
    std::shared_ptr<Expression> right);

  BinaryExpression(
    BinaryOperator op,
    std::shared_ptr<Expression> left,
    std::shared_ptr<Expression> right);

  ~BinaryExpression();

  const BinaryOperator op;
  const std::shared_ptr<Expression> left;
  const std::shared_ptr<Expression> right;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
