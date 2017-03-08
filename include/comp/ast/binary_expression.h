#pragma once

#include "expression.h"

namespace comp {
namespace ast {
struct BinaryExpression : public Expression {
  enum class Operator {
    Addition,
    Subtraction,
    Division,
    Multiplication,
    Remainder,
  };

  static std::shared_ptr<BinaryExpression> create(
    Operator op,
    std::shared_ptr<Expression> left,
    std::shared_ptr<Expression> right,
    std::shared_ptr<SourceLocation> location
  );

  BinaryExpression(
    Operator op,
    std::shared_ptr<Expression> left,
    std::shared_ptr<Expression> right,
    std::shared_ptr<SourceLocation> location
  );

  virtual ~BinaryExpression();

  const Operator op;
  const std::shared_ptr<Expression> left;
  const std::shared_ptr<Expression> right;
};
}
}
