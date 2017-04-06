#pragma once

#include <memory>
#include <set>
#include <vector>

#include "comp/ir/basic_block.h"

namespace comp {
namespace ir {
class ControlFlowGraph {
 public:
  static std::unique_ptr<ControlFlowGraph> Create(std::shared_ptr<BasicBlock> source = std::make_shared<BasicBlock>());
  ControlFlowGraph(std::shared_ptr<BasicBlock> source = std::make_shared<BasicBlock>());

  virtual ~ControlFlowGraph();

  std::shared_ptr<BasicBlock> CreateBasicBlock(
    std::vector<std::shared_ptr<Op>> ops = std::vector<std::shared_ptr<Op>>());

  std::set<std::shared_ptr<BasicBlock>> GetBasicBlocks() const;

  std::shared_ptr<BasicBlock> GetSource() const;

 private:
  const std::shared_ptr<BasicBlock> source_;
  std::set<std::shared_ptr<BasicBlock>> blocks_;
};
}
}
