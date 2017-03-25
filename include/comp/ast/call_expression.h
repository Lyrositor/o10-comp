#pragma once

#include <vector>
#include "comp/ast/expression.h"

namespace comp {
namespace ast {

struct CallExpression final : public RExpression {
  static std::unique_ptr<CallExpression> Create(
    std::shared_ptr<RExpression> callee,
    std::vector<std::shared_ptr<RExpression>> arguments,
    std::shared_ptr<SourceLocation> location = nullptr);

  CallExpression(
    std::shared_ptr<RExpression> callee,
    std::vector<std::shared_ptr<RExpression>> arguments,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~CallExpression();

  const std::shared_ptr<RExpression> callee;
  std::vector<std::shared_ptr<RExpression>> arguments;
};
}  // namespace ast
}  // namespace comp
