#include <comp/ir/basic_block.h>

namespace comp {
namespace ir {
std::unique_ptr<BasicBlock> BasicBlock::create(
  std::vector<std::shared_ptr<Op>> ops) {
  return std::unique_ptr<BasicBlock>(new BasicBlock(std::move(ops)));
}

BasicBlock::BasicBlock(
  std::vector<std::shared_ptr<Op>> ops) : ops_(std::move(ops)) {
}

void BasicBlock::Push(std::shared_ptr<Op> op) {
  this->ops_.push_back(op);
}

BasicBlock::~BasicBlock() {
}
}  // namespace ir
}  // namespace comp
