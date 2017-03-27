#pragma once

#include <memory>
#include <vector>

#include "comp/ir/op.h"

namespace comp {
namespace ir {
class BasicBlock {
 public:
  static std::unique_ptr<BasicBlock> Create(
    std::vector<std::shared_ptr<Op>> ops = std::vector<std::shared_ptr<Op>>());

  BasicBlock(
    std::vector<std::shared_ptr<Op>> ops = std::vector<std::shared_ptr<Op>>());

  virtual ~BasicBlock();

  void Push(std::shared_ptr<Op> op);

  std::shared_ptr<BasicBlock> GetBranchIfTrue();

  void SetBranchIfTrue(std::shared_ptr<BasicBlock> branchIfTrue);

  std::shared_ptr<BasicBlock> GetBranchIfFalse();

  void SetBranchIfFalse(std::shared_ptr<BasicBlock> branchIfFalse);

 private:
  std::vector<std::shared_ptr<Op>> ops_;
  std::weak_ptr<BasicBlock> branch_if_true_;
  /* nullptr if it is a simple jump */
  std::weak_ptr<BasicBlock> branch_if_false_;
};
}  // namespace ir
}  // namespace comp
