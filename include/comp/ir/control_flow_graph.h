#pragma once

#include <memory>
#include <set>

#include "comp/ir/basic_block.h"

namespace comp {
namespace ir {
class ControlFlowGraph {
 public:
  static std::unique_ptr<ControlFlowGraph> Create();

  ControlFlowGraph();

  virtual ~ControlFlowGraph();

  std::shared_ptr<BasicBlock> CreateBasicBlock(
    std::vector<std::shared_ptr<Op>> ops = std::vector<std::shared_ptr<Op>>());

  std::set<std::shared_ptr<BasicBlock>> GetBasicBlocks();

 private:
  std::set<std::shared_ptr<BasicBlock>> blocks_;
};
}
}
