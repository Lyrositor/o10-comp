#pragma once

#include <memory>
#include <vector>
#include "statement.h"
#include "expression.h"

namespace comp {
namespace ast {
struct BlockStatement final : public Statement {
  BlockStatement(std::vector<std::shared_ptr<Statement>> body, std::shared_ptr<SourceLocation> location = nullptr);
  ~BlockStatement();

  const std::vector<std::shared_ptr<Statement>> body;
};
}
}