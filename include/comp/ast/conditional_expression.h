#pragma once

#include "comp/ast/expression.h"

namespace comp {
namespace ast {
struct ConditionalExpression final : public RExpression {
  static std::unique_ptr<ConditionalExpression> Create(
    std::shared_ptr<RExpression> test,
    std::shared_ptr<RExpression> consequence,
    std::shared_ptr<RExpression> alternative,
    std::shared_ptr<SourceLocation> location = nullptr);

  ConditionalExpression(
    std::shared_ptr<RExpression> test,
    std::shared_ptr<RExpression> consequence,
    std::shared_ptr<RExpression> alternative,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~ConditionalExpression();

  const std::shared_ptr<RExpression> test;
  const std::shared_ptr<RExpression> consequence;
  const std::shared_ptr<RExpression> alternative;
};
}  // namespace ast
}  // namespace comp
