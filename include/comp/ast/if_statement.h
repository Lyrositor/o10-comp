#pragma once

#include <memory>
#include "expression.h"
#include "statement.h"

namespace comp {
namespace ast {
struct IfStatement : public Statement {
  IfStatement(
    std::shared_ptr<Expression> test,
    std::shared_ptr<Statement> consequence,
    std::shared_ptr<Statement> alternative
  );
  ~IfStatement();

  const std::shared_ptr<Expression> test;
  const std::shared_ptr<Statement> consequence;
  const std::shared_ptr<Statement> alternative;
};
}
}
