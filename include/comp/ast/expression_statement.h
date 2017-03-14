#pragma once

#include <memory>
#include "statement.h"
#include "expression.h"

namespace comp {
namespace ast {
struct ExpressionStatement final : public Statement {
  ExpressionStatement(std::shared_ptr<Expression> expression, std::shared_ptr<SourceLocation> location = nullptr);
  ~ExpressionStatement();

  const std::shared_ptr<Expression> expression;
};
}
}
