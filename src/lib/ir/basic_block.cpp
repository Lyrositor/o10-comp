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

void BasicBlock::Push(std::shared_ptr<Op> op) {
  this->ops_.push_back(op);
}

std::shared_ptr<BasicBlock> BasicBlock::GetBranchIfTrue() {
  return this->branchIfTrue_;
}

void BasicBlock::SetBranchIfTrue(std::shared_ptr<BasicBlock> branchIfTrue) {
  this->branchIfTrue_ = branchIfTrue;
}

std::shared_ptr<BasicBlock> BasicBlock::GetBranchIfFalse() {
  return this->branchIfFalse_;
}

void BasicBlock::SetBranchIfFalse(std::shared_ptr<BasicBlock> branchIfFalse) {
  this->branchIfFalse_ = branchIfFalse;
}

BasicBlock::~BasicBlock() {
}
}  // namespace ir
}  // namespace comp
