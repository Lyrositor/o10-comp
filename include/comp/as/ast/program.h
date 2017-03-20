#pragma once

#include <memory>
#include <vector>
#include "comp/as/ast/node.h"
#include "comp/as/ast/statement.h"

namespace comp {
namespace as {
namespace ast {
struct Program final : public Node {
  std::unique_ptr<Program> Create(std::vector<std::shared_ptr<Statement>> body);

  Program(std::vector<std::shared_ptr<Statement>> body);

  ~Program();

  std::vector<std::shared_ptr<Statement>> body;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
