#pragma once

#include <memory>
#include <vector>
#include "comp/as/ast/node.h"
#include "comp/as/ast/symbol.h"

namespace comp {
namespace as {
namespace ast {
struct Statement : public Node {
  Statement(Type node_type, std::vector<std::shared_ptr<Symbol>> labels);

  virtual ~Statement() = 0;

  std::vector<std::shared_ptr<Symbol>> labels;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
