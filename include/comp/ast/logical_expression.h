#pragma once

#include "expression.h"

namespace comp {
namespace ast {
enum class LogicalOperator {
  LogicalAnd, // left && right
  LogicalOr, // left || right
};

struct LogicalExpression : public RExpression {
  static std::unique_ptr<LogicalExpression> Create(
      LogicalOperator op,
      std::shared_ptr<RExpression> left,
      std::shared_ptr<RExpression> right,
      std::shared_ptr<SourceLocation> location = nullptr);

  LogicalExpression(
      LogicalOperator op,
  std::shared_ptr<RExpression> left,
      std::shared_ptr<RExpression> right,
  std::shared_ptr<SourceLocation> location = nullptr);

  ~LogicalExpression();

  const LogicalOperator op;
  const std::shared_ptr<RExpression> left;
  const std::shared_ptr<RExpression> right;
};
}
}