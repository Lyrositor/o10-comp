#pragma once

#include "expression.h"
#include "statement.h"

namespace comp {
namespace ast {

struct ReturnStatement final : public Statement {
  static std::unique_ptr<ReturnStatement> Create(
    std::shared_ptr<Expression> expression,
    std::shared_ptr<SourceLocation> location = nullptr
  );

  ReturnStatement(
    std::shared_ptr<Expression> expression,
    std::shared_ptr<SourceLocation> location = nullptr
  );
  ~ReturnStatement();

  const std::shared_ptr<Expression> expression;
};
}
}
