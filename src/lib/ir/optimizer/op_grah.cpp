#include <comp/ir/optimizer/op_graph.h>

namespace comp {
namespace ir {
namespace optimizer {
std::unique_ptr<OpGraph> OpGraph::Create() {
  return std::unique_ptr<OpGraph>(new OpGraph());
}

std::unique_ptr<OpGraph> OpGraph::FromControlFlowGraph(std::shared_ptr<ControlFlowGraph> cfg) {
  throw std::runtime_error("Not implemented: `FromControlFlowGraph`");
}

OpGraph::OpGraph():
  vertices(),
  edges(),
  out_edges(),
  in_edges(){
}

OpGraph::~OpGraph() {
}

void OpGraph::AddVertex(Vertex node) {
  this->vertices.insert(node);
}

void OpGraph::AddEdge(Edge edge) {
  if (!this->HasVertex(edge.first)) {
    throw std::runtime_error("Cannot add edge from a vertex not in the graph");
  }
  if (!this->HasVertex(edge.second)) {
    throw std::runtime_error("Cannot add edge to a vertex not in the graph");
  }
  this->edges.insert(edge);

  if (this->out_edges.find(edge.first) == this->out_edges.end()) {
    this->out_edges[edge.first] = std::unique_ptr<std::set<Vertex>>(new std::set<Vertex>());
  }
  this->out_edges[edge.first]->insert(edge.second);

  if (this->in_edges.find(edge.second) == this->in_edges.end()) {
    this->in_edges[edge.second] = std::unique_ptr<std::set<Vertex>>(new std::set<Vertex>());
  }
  this->in_edges[edge.second]->insert(edge.first);
}

bool OpGraph::HasVertex(Vertex node) const {
  return this->vertices.find(node) != this->vertices.end();
}

bool OpGraph::HasEdge(Edge edge) const {
  return this->edges.find(edge) != this->edges.end();
}

std::unique_ptr<ControlFlowGraph> OpGraph::ToControlFlowGraph() const {
  throw std::runtime_error("Not implemented: `ToControlFlowGraph`");
}
}  // namespace optimizer
}  // namespace ir
}  // namespace comp
