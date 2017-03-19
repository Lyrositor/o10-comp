#pragma once

#include "comp/ast/expression.h"

namespace comp {
namespace ast {
enum class BinaryOperator {
  Addition,
  Subtraction,
  Division,
  Multiplication,
  Remainder,
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
