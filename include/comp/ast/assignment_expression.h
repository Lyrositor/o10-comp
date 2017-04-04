#pragma once

#include "comp/ast/binary_expression.h"
#include "comp/ast/expression.h"

namespace comp {
namespace ast {
enum class AssignmentOperator {
  Addition, // lvalue += rvalue
  BitwiseAnd, // lvalue &= rvalue
  BitwiseOr, // lvalue |= rvalue
  BitwiseXor, // lvalue ^= rvalue
  Division, // lvalue /= rvalue
  LeftShift, // lvalue <<= rvalue
  Multiplication, // lvalue *= rvalue
  Remainder, // lvalue %= rvalue
  RightShift, // lvalue >>= rvalue
  Simple, // lvalue = rvalue
  Subtraction // lvalue -= rvalue
};

struct AssignmentExpression final : public RExpression {
  static std::unique_ptr<AssignmentExpression> Create(
    std::shared_ptr<LExpression> left,
    std::shared_ptr<RExpression> right,
    AssignmentOperator op = AssignmentOperator::Simple,
    std::shared_ptr<SourceLocation> location = nullptr);

  AssignmentExpression(
    std::shared_ptr<LExpression> left,
    std::shared_ptr<RExpression> right,
    AssignmentOperator op = AssignmentOperator::Simple,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~AssignmentExpression();

  const std::shared_ptr<LExpression> left;
  const std::shared_ptr<RExpression> right;
  const AssignmentOperator op;
};
}  // namespace ast
}  // namespace comp
