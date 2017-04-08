#include <comp/ir/optimizer/op_graph.h>
#include <set>
#include <stack>
#include <cassert>

namespace comp {
namespace ir {
namespace optimizer {
std::unique_ptr<OpGraph> OpGraph::Create() {
  return std::unique_ptr<OpGraph>(new OpGraph());
}

std::unique_ptr<OpGraph> OpGraph::FromControlFlowGraph(const ControlFlowGraph &cfg) {
  std::unique_ptr<OpGraph> result = OpGraph::Create();
  std::set<std::shared_ptr<BasicBlock>> basic_blocks = cfg.GetBasicBlocks();
  for (auto basic_block : basic_blocks) {
    if (basic_block->GetType() == BasicBlock::Type::Incomplete) {
      throw std::runtime_error("Cannot build operations graph from control flow containing incomplete basic blocks");
    }
    for (Vertex op : basic_block->GetOps()) {
      result->AddVertex(op);
    }
  }
  for (auto basic_block : basic_blocks) {
    std::vector<Vertex> ops = basic_block->GetOps();
    for (size_t i = 0, l = ops.size() - 1; i < l; i++) {
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
  result->source_ = cfg.GetSource()->GetOps()[0];
  return std::move(result);
}

OpGraph::OpGraph() :
  source_(),
  vertices_(),
  edges_(),
  out_edges_(),
  in_edges_() {
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

std::set<Vertex> OpGraph::GetInEdges(const Vertex vertex) const {
  assert(this->HasVertex(vertex));
  return *this->in_edges_.find(vertex)->second;
}

std::pair<Vertex, Vertex> OpGraph::GetOutEdges(const Vertex vertex) const {
  assert(this->HasVertex(vertex));
  return *this->out_edges_.find(vertex)->second;
}

Vertex OpGraph::GetSource() const {
  return this->source_;
}

enum class VertexColor {
  White,
  Gray,
  Black
};

void OpGraph::Dfs(std::function<void(const Vertex &)> visitor) const {
  const Vertex source = this->GetSource();
  if (source == nullptr) {
    return;
  }
  std::map<Vertex, VertexColor> vertices;
  for (Vertex v : this->vertices_) {
    vertices[v] = VertexColor::White;
  }
  std::stack<Vertex> open_set;

  open_set.push(source);
  vertices[source] = VertexColor::Gray;

  Vertex current_vertex;
  while (open_set.size() > 0) {
    current_vertex = open_set.top();
    open_set.pop();
    vertices[current_vertex] = VertexColor::Black;
    visitor(current_vertex);
    const Edge out_edges = this->GetOutEdges(current_vertex);
    // Push `.first` at the top to follow the "branch if true" path
    // in priority when there is a `TestOp`.
    for (Vertex v : {out_edges.second, out_edges.first}) {
      if (v == nullptr) {
        continue;
      } else if (vertices[v] == VertexColor::White) {
        open_set.push(v);
        vertices[v] = VertexColor::Gray;
      }
    }
  }
}

std::unique_ptr<ControlFlowGraph> OpGraph::ToControlFlowGraph() const {
  std::unique_ptr<ControlFlowGraph> result = ControlFlowGraph::Create();
  const Vertex source = this->GetSource();
  if (source == nullptr) {
    return result;
  }

  // A basic starts either with the source operation or is an operation
  // with more than one in-edge. This map stores the operation that
  // start a basic block.
  std::map<Vertex, std::shared_ptr<BasicBlock>> block_heads;
  block_heads[source] = result->GetSource();

  this->Dfs([&, &block_heads, &result](const Vertex &v) -> void {
    if (this->GetInEdges(v).size() > 1) {
      if (block_heads.find(v) == block_heads.end()) {
        block_heads[v] = result->CreateBasicBlock();
      }
    }
  });

  // The block corresponding to the current branch
  std::shared_ptr<BasicBlock> current_block = nullptr;
  this->Dfs([&, &block_heads, &current_block](const Vertex &v) -> void {
    if (current_block == nullptr) {
      current_block = block_heads[v];
    }
    const Edge out_edges = this->GetOutEdges(v);
    if (out_edges.first == nullptr) {
      // End block: Return or Final
      if (v->op_type == Op::Type::ReturnOp) {
        current_block->SetReturn(std::static_pointer_cast<ReturnOp>(v)->in);
        current_block = nullptr;
      } else {
        current_block->Push(v);
        current_block->SetFinal();
        current_block = nullptr;
      }
    } else if (out_edges.second != nullptr) {
      // Two edges: ConditionalJump
      assert(v->op_type == Op::Type::TestOp);
      assert(block_heads.find(out_edges.first) != block_heads.end());
      assert(block_heads.find(out_edges.second) != block_heads.end());
      current_block->SetConditionalJump(
        std::static_pointer_cast<TestOp>(v)->test,
        block_heads[out_edges.first],
        block_heads[out_edges.second]
      );
      current_block = nullptr;
    } else {
      current_block->Push(v);
      if (block_heads.find(out_edges.first) != block_heads.end()) {
        current_block->SetJump(block_heads[out_edges.first]);
        current_block = nullptr;
      }
    }
  });

  return std::move(result);
}
}  // namespace optimizer
}  // namespace ir
}  // namespace comp
