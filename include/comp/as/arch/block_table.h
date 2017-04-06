#pragma once

#include <memory>
#include <unordered_map>

#include "comp/as/ast.h"
#include "comp/ir/basic_block.h"

namespace comp {
namespace as {
namespace arch {
class BlockTable {
 public:
  void Register(
    std::shared_ptr<ir::BasicBlock> block,
    std::shared_ptr<ast::Symbol> symbol);

  std::shared_ptr<ast::Symbol> Get(std::shared_ptr<ir::BasicBlock> block) const;

  bool Contains(std::shared_ptr<ir::BasicBlock> block) const;

 private:
  std::unordered_map<
    std::shared_ptr<ir::BasicBlock>,
    std::shared_ptr<ast::Symbol>> blocks_;
};
}  // namespace arch
}  // namespace as
}  // namespace comp
