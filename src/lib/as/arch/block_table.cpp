#include <comp/as/arch/block_table.h>

namespace comp {
namespace as {
namespace arch {
void BlockTable::Register(
  std::shared_ptr<ir::BasicBlock> block,
  std::shared_ptr<ast::Symbol> symbol) {
  blocks_[block] = symbol;
}

std::shared_ptr<ast::Symbol> BlockTable::Get(
  std::shared_ptr<ir::BasicBlock> block) const {
  return blocks_.at(block);
}

bool BlockTable::Contains(std::shared_ptr<ir::BasicBlock> block) const {
  return blocks_.find(block) != blocks_.end();
}
}  // namespace arch
}  // namespace as
}  // namespace comp
