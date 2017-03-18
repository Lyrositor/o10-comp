#pragma once

#include "comp/ast/binary_expression.h"
#include "comp/ast/expression.h"

namespace comp {
namespace ast {
struct AssignmentExpression final : public RExpression {
  static std::unique_ptr<AssignmentExpression> Create(
    std::shared_ptr<LExpression> lvalue,
    std::shared_ptr<RExpression> rvalue,
    BinaryOperator op = BinaryOperator::None,
    std::shared_ptr<SourceLocation> location = nullptr);

  AssignmentExpression(
    std::shared_ptr<LExpression> lvalue,
    std::shared_ptr<RExpression> rvalue,
    BinaryOperator op = BinaryOperator::None,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~AssignmentExpression();

  const std::shared_ptr<LExpression> lvalue;
  const std::shared_ptr<RExpression> rvalue;
  const BinaryOperator op;
};
}  // namespace ast
}  // namespace comp
