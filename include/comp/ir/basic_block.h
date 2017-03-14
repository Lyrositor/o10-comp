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

  void push(std::shared_ptr<Op> op);

  virtual ~BasicBlock();
 private:
  std::vector<std::shared_ptr<Op>> ops;
  std::shared_ptr<BasicBlock> branchIfTrue;
  std::shared_ptr<BasicBlock> branchIfFalse;
};
}
}
