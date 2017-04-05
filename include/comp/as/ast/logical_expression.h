#pragma once

#include <memory>
#include "comp/as/ast/address_expression.h"

namespace comp {
namespace as {
namespace ast {
enum class LogicalOperator {
  LogicalAnd, // left && right
  LogicalOr, // left || right
};

struct LogicalExpression final : public AddressExpression {
  static std::unique_ptr<LogicalExpression> Create(
      LogicalOperator op,
      std::shared_ptr<AddressExpression> left,
      std::shared_ptr<AddressExpression> right);

  LogicalExpression(
      LogicalOperator op,
      std::shared_ptr<AddressExpression> left,
      std::shared_ptr<AddressExpression> right);

  ~LogicalExpression();

  const LogicalOperator op;
  const std::shared_ptr<AddressExpression> left;
  const std::shared_ptr<AddressExpression> right;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
