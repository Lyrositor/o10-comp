#include <comp/ir/control_flow_graph.h>

namespace comp {
namespace ir {
std::unique_ptr<ControlFlowGraph> ControlFlowGraph::Create() {
  return std::unique_ptr<ControlFlowGraph>(new ControlFlowGraph());
}

ControlFlowGraph::ControlFlowGraph() :
  source_(std::unique_ptr<BasicBlock>(new BasicBlock())) {
}

ControlFlowGraph::~ControlFlowGraph() {
}

std::shared_ptr<BasicBlock> ControlFlowGraph::CreateBasicBlock(
  std::vector<std::shared_ptr<Op>> ops
) {
  std::shared_ptr<BasicBlock> block = BasicBlock::Create(ops);
  blocks_.insert(block);
  return block;
}

std::set<std::shared_ptr<BasicBlock>> ControlFlowGraph::GetBasicBlocks() const {
  return blocks_;
}

std::shared_ptr<BasicBlock> ControlFlowGraph::GetSource() const {
  return source_;
}
}  // namespace ir
}  // namespace comp
