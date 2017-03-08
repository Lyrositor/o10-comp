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

struct BinaryExpression final : public Expression {
  static std::shared_ptr<BinaryExpression> create(
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

  virtual ~BinaryExpression();

  const BinaryOperator op;
  const std::shared_ptr<Expression> left;
  const std::shared_ptr<Expression> right;
};
}
}
