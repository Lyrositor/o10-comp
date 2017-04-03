#include <comp/ir/basic_block.h>

namespace comp {
namespace ir {
std::unique_ptr<BasicBlock> BasicBlock::Create(
  std::vector<std::shared_ptr<Op>> ops) {
  return std::unique_ptr<BasicBlock>(new BasicBlock(std::move(ops)));
}

BasicBlock::BasicBlock(
  std::vector<std::shared_ptr<Op>> ops) : ops_(std::move(ops)) {
}

std::vector<std::shared_ptr<Op>> BasicBlock::GetOps() const {
  return this->ops_;
}

void BasicBlock::Push(std::shared_ptr<Op> op) {
  this->ops_.push_back(op);
}

std::weak_ptr<BasicBlock> BasicBlock::GetBranchIfTrue() const {
  return this->branch_if_true_;
}

void BasicBlock::SetBranchIfTrue(std::shared_ptr<BasicBlock> branchIfTrue) {
  this->branch_if_true_ = branchIfTrue;
}

std::weak_ptr<BasicBlock> BasicBlock::GetBranchIfFalse() const {
  return this->branch_if_false_;
}

void BasicBlock::SetBranchIfFalse(std::shared_ptr<BasicBlock> branchIfFalse) {
  this->branch_if_true_ = branchIfFalse;
}

BasicBlock::~BasicBlock() {
}
}  // namespace ir
}  // namespace comp
