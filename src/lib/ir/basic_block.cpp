#include <comp/ir/basic_block.h>

namespace comp {
namespace ir {
std::unique_ptr<BasicBlock> BasicBlock::create(std::vector<std::shared_ptr<Op>> ops) {
  return std::unique_ptr<BasicBlock>(new BasicBlock(std::move(ops)));
}

BasicBlock::BasicBlock(std::vector<std::shared_ptr<Op>> ops) : ops(std::move(ops)) {
}

void BasicBlock::push(std::shared_ptr<Op> op) {
  this->ops.push_back(op);
}

BasicBlock::~BasicBlock() {
}
}
}
