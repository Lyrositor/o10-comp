#include <comp/ir/optimizer/op_graph.h>

namespace comp {
namespace ir {
namespace optimizer {
std::unique_ptr<OpGraph> OpGraph::Create() {
  return std::unique_ptr<OpGraph>(new OpGraph());
}

std::unique_ptr<OpGraph> OpGraph::FromControlFlowGraph(std::shared_ptr<ControlFlowGraph> cfg) {
  std::unique_ptr<OpGraph> result = OpGraph::Create();
  std::set<std::shared_ptr<BasicBlock>> basic_blocks = cfg->GetBasicBlocks();
  for(auto basic_block : basic_blocks) {
    if (basic_block->GetType() == BasicBlock::Type::Incomplete) {
      throw std::runtime_error("Cannot build operations graph from control flow containing incomplete basic blocks");
    }
    for(Vertex op : basic_block->GetOps()) {
      result->AddVertex(op);
    }
  }
  for(auto basic_block : basic_blocks) {
    std::vector<Vertex> ops = basic_block->GetOps();
    for(size_t i = 0, l = ops.size() - 1; i < l; i++) {
      result->AddEdge(ops[i], ops[i + 1]);
    }
    switch (basic_block->GetType()) {
      case BasicBlock::Type::Final:
      case BasicBlock::Type::Return: {
        break;
      }
      case BasicBlock::Type::Jump: {
        Vertex target = basic_block->GetBranch()->GetOps()[0];
        result->AddEdge(ops[ops.size() - 1], target);
        break;
      }
      case BasicBlock::Type::ConditionalJump: {
        Vertex target_if_true = basic_block->GetBranchIfTrue()->GetOps()[0];
        Vertex target_if_false = basic_block->GetBranchIfFalse()->GetOps()[0];
        result->AddConditionalEdges(ops[ops.size() - 1], target_if_true, target_if_false);
        break;
      }
      default: {
        throw std::domain_error("Unexpected value for `basic_block->GetType()` in `FromControlFlowGraph`");
      }
    }
  }
  return result;
}

OpGraph::OpGraph():
  vertices_(),
  edges_(),
  out_edges_(),
  in_edges_(){
}

OpGraph::~OpGraph() {
}

void OpGraph::AddVertex(Vertex node) {
  this->vertices_.insert(node);
}

void OpGraph::AddEdge(Vertex source, Vertex target) {
  if (source->op_type == Op::Type::TestOp) {
    throw std::runtime_error("Use `AddConditionalEdge` for `TestOp`");
  }
  if (source->op_type == Op::Type::ReturnOp) {
    throw std::runtime_error("Cannot add edge from `ReturnOp`");
  }
  if (!this->HasVertex(source)) {
    throw std::runtime_error("Cannot add edge from a vertex not in the graph");
  }
  if (!this->HasVertex(target)) {
    throw std::runtime_error("Cannot add edge to a vertex not in the graph");
  }
  if (this->out_edges_.find(source) != this->out_edges_.end()) {
    throw std::runtime_error("The source node already has an out edge");
  }
  if (this->in_edges_.find(target) == this->in_edges_.end()) {
    this->in_edges_[target] = std::unique_ptr<std::set<Vertex>>(new std::set<Vertex>());
  }

  Edge edge(source, target);
  this->edges_.insert(edge);
  // Use a virtual edge
  this->out_edges_[source] = std::unique_ptr<Edge>(new Edge(target, nullptr));
  this->in_edges_[target]->insert(source);
}

void OpGraph::AddConditionalEdges(Vertex source, Vertex target_if_true, Vertex target_if_false) {
  if (source->op_type != Op::Type::TestOp) {
    throw std::runtime_error("Use `AddEdge` for non-`TestOp`");
  }
  if (!this->HasVertex(source)) {
    throw std::runtime_error("Cannot add edge from a vertex not in the graph");
  }
  if (!this->HasVertex(target_if_true)) {
    throw std::runtime_error("Cannot add edge_if_true to a vertex not in the graph");
  }
  if (!this->HasVertex(target_if_false)) {
    throw std::runtime_error("Cannot add edge_false to a vertex not in the graph");
  }
  if (this->out_edges_.find(source) != this->out_edges_.end()) {
    throw std::runtime_error("The source node already has an out edge");
  }
  if (this->in_edges_.find(target_if_true) == this->in_edges_.end()) {
    this->in_edges_[target_if_true] = std::unique_ptr<std::set<Vertex>>(new std::set<Vertex>());
  }
  if (this->in_edges_.find(target_if_false) == this->in_edges_.end()) {
    this->in_edges_[target_if_false] = std::unique_ptr<std::set<Vertex>>(new std::set<Vertex>());
  }

  Edge edge_if_true(source, target_if_true);
  Edge edge_if_false(source, target_if_false);
  this->edges_.insert(edge_if_true);
  this->edges_.insert(edge_if_false);
  // Use a virtual edge
  this->out_edges_[source] = std::unique_ptr<Edge>(new Edge(target_if_true, target_if_false));
  this->in_edges_[target_if_true]->insert(source);
  this->in_edges_[target_if_false]->insert(source);
}

bool OpGraph::HasVertex(Vertex node) const {
  return this->vertices_.find(node) != this->vertices_.end();
}

bool OpGraph::HasEdge(Edge edge) const {
  return this->edges_.find(edge) != this->edges_.end();
}

std::unique_ptr<ControlFlowGraph> OpGraph::ToControlFlowGraph() const {
  throw std::runtime_error("Not implemented: `ToControlFlowGraph`");
}
}  // namespace optimizer
}  // namespace ir
}  // namespace comp
