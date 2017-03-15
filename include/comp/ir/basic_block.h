#pragma once

#include <vector>
#include <memory>
#include "op.h"

namespace comp {
namespace ir {
class BasicBlock {
 public:
  static std::unique_ptr<BasicBlock> create(std::vector<std::shared_ptr<Op>> ops = std::vector<std::shared_ptr<Op>>());

  BasicBlock(std::vector<std::shared_ptr<Op>> ops = std::vector<std::shared_ptr<Op>>());

  virtual ~BasicBlock();

  void Push(std::shared_ptr<Op> op);

 private:
  std::vector<std::shared_ptr<Op>> ops_;
  std::shared_ptr<BasicBlock> branchIfTrue_;
  std::shared_ptr<BasicBlock> branchIfFalse_;
};
}
}
