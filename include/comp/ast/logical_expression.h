#pragma once

#include <string>

#include "comp/ast/expression.h"

namespace comp {
namespace ast {
enum class LogicalOperator {
  LogicalAnd,  // left && right
  LogicalOr,  // left || right
};

std::string LogicalOperatorToString(LogicalOperator op);

struct LogicalExpression final : public RExpression {
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
