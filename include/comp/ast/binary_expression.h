#pragma once

#include "comp/ast/expression.h"

namespace comp {
namespace ast {
enum class BinaryOperator {
  Addition, // left + right
  BitwiseAnd, // left & right
  BitwiseOr, // left | right
  BitwiseXor, // left ^ right
  Comma, // left, right
  Division, // left / right
  Equality, // left == right
  GreaterThan, // left > right
  GreaterThanOrEqual, // left >= right
  Inequality, // left != right
  LeftShift, // left << right
  LessThan, // left < right
  LessThanOrEqualTo, // left <= right
  LogicalAnd, // left && right
  LogicalOr, // left || right
  Multiplication, // left * right
  Remainder, // left % right
  RightShift, // left >> right
  Subtraction // left - right
};

/**
 * Represents an expression obtained by applying a binary operator.
 *
 * Examples:
 *
 * ```
 * a + b
 * ```
 *
 * ```
 * c / 4
 * ```
 */
struct BinaryExpression final : public RExpression {
  static std::unique_ptr<BinaryExpression> Create(
    BinaryOperator op,
    std::shared_ptr<RExpression> left,
    std::shared_ptr<RExpression> right,
    std::shared_ptr<SourceLocation> location = nullptr);

  BinaryExpression(
    BinaryOperator op,
    std::shared_ptr<RExpression> left,
    std::shared_ptr<RExpression> right,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~BinaryExpression();

  const BinaryOperator op;
  const std::shared_ptr<RExpression> left;
  const std::shared_ptr<RExpression> right;
};
}  // namespace ast
}  // namespace comp
