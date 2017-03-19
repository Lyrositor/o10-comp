#pragma once

#include "comp/ast/binary_expression.h"
#include "comp/ast/expression.h"

namespace comp {
namespace ast {
enum class AssignmentOperator {
  Simple,
  Multiplication,
  Division,
  Remainder,
  Addition,
  Subtraction,
  LeftShift,
  RightShift,
  And,
  Xor,
  Or
};

struct AssignmentExpression final : public RExpression {
  static std::unique_ptr<AssignmentExpression> Create(
    std::shared_ptr<LExpression> lvalue,
    std::shared_ptr<RExpression> rvalue,
    AssignmentOperator op = AssignmentOperator::Simple,
    std::shared_ptr<SourceLocation> location = nullptr);

  AssignmentExpression(
    std::shared_ptr<LExpression> lvalue,
    std::shared_ptr<RExpression> rvalue,
    AssignmentOperator op = AssignmentOperator::Simple,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~AssignmentExpression();

  const std::shared_ptr<LExpression> lvalue;
  const std::shared_ptr<RExpression> rvalue;
  const AssignmentOperator op;
};
}  // namespace ast
}  // namespace comp
