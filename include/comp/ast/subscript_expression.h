#pragma once

#include <memory>
#include "comp/ast/expression.h"

namespace comp {
namespace ast {

struct SubscriptExpression final : public LExpression {
  static std::unique_ptr<SubscriptExpression> Create(
    std::shared_ptr<RExpression> array,
    std::shared_ptr<RExpression> index,
    std::shared_ptr<SourceLocation> location = nullptr);

  SubscriptExpression(
    std::shared_ptr<RExpression> array,
    std::shared_ptr<RExpression> index,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~SubscriptExpression();

  const std::shared_ptr<RExpression> array;
  const std::shared_ptr<RExpression> index;
};
}  // namespace ast
}  // namespace comp
