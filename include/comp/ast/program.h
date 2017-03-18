#pragma once

#include <memory>
#include <vector>

#include "comp/ast/declaration.h"
#include "comp/ast/node.h"

namespace comp {
namespace ast {
struct Program final : public Node {
  static std::unique_ptr<Program> Create(
    std::vector<std::shared_ptr<Declaration>> body,
    std::shared_ptr<SourceLocation> location = nullptr);

  Program(
    std::vector<std::shared_ptr<Declaration>> body,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~Program();

  const std::vector<std::shared_ptr<Declaration>> body;
};
}  // namespace ast
}  // namespace comp
