#pragma once

#include <memory>
#include "comp/as/ast/node.h"
#include "comp/as/ast/statement.h"

namespace comp {
namespace as {
namespace ast {
struct EmptyStatement final : public Statement {
  static std::unique_ptr<EmptyStatement> Create(std::vector<std::shared_ptr<Symbol>> labels = {});

  EmptyStatement(std::vector<std::shared_ptr<Symbol>> labels = {});

  ~EmptyStatement();
};
}  // namespace ast
}  // namespace as
}  // namespace comp
