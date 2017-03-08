#pragma once

#include <memory>
#include "statement.h"
#include "expression.h"

namespace comp {
namespace ast {
struct ExpressionStatement : public Statement {
  ExpressionStatement(std::unique_ptr<Expression> expression);
  ~ExpressionStatement();

  const std::unique_ptr<Expression> expression;
};
}
}
