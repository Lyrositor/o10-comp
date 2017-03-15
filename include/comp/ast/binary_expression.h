#pragma once

#include "expression.h"

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
struct BinaryExpression final : public Expression {
  static std::unique_ptr<BinaryExpression> Create(
    BinaryOperator op,
    std::shared_ptr<Expression> left,
    std::shared_ptr<Expression> right,
    std::shared_ptr<SourceLocation> location = nullptr
  );

  BinaryExpression(
    BinaryOperator op,
    std::shared_ptr<Expression> left,
    std::shared_ptr<Expression> right,
    std::shared_ptr<SourceLocation> location = nullptr
  );

  ~BinaryExpression();

  const BinaryOperator op;
  const std::shared_ptr<Expression> left;
  const std::shared_ptr<Expression> right;
};
}
}
