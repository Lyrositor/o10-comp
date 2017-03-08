#pragma once

#include <memory>
#include <vector>
#include "statement.h"
#include "expression.h"

namespace comp {
namespace ast {
struct BlockStatement : public Statement {
  BlockStatement(std::vector<std::shared_ptr<Statement>> body);
  ~BlockStatement();

  const std::vector<std::shared_ptr<Statement>> body;
};
}
}
