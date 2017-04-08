#pragma once

#include <memory>

#include "comp/ast/expression.h"

namespace comp {
namespace ast {
enum class UnaryOperator {
  AddressOf, // &expression
  BitwiseComplement, // ~expression
  Indirection, // *expression
  LogicalNegation, // !expression
  PostfixDecrement, // expression--
  PostfixIncrement, // expression++
  PrefixDecrement, // --expression
  PrefixIncrement, // ++expression
  UnaryMinus, // -expression
  UnaryPlus // +expression
};

struct UnaryExpression final : public RExpression {
  static std::unique_ptr<UnaryExpression> Create(
    UnaryOperator op,
    std::shared_ptr<RExpression> expression,
    std::shared_ptr<SourceLocation> location = nullptr);

  UnaryExpression(
    UnaryOperator op,
    std::shared_ptr<RExpression> expression,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~UnaryExpression();

  const UnaryOperator op;
  const std::shared_ptr<RExpression> expression;
};
}  // namespace ast
}  // namespace comp
