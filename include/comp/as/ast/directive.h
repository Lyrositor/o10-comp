#pragma once

#include <memory>
#include "comp/as/ast/node.h"
#include "comp/as/ast/statement.h"

namespace comp {
namespace as {
namespace ast {
struct Directive : public Statement {
  Directive(
      Type node_type,
      std::vector<std::shared_ptr<Symbol>> labels = {});

  virtual ~Directive() = 0;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
