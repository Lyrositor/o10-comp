#pragma once

#include <map>
#include <memory>
#include <set>
#include <comp/ir/control_flow_graph.h>
#include <comp/ir/op.h>

namespace comp {
namespace ir {
namespace optimizer {
typedef std::shared_ptr<Op> Vertex;
typedef std::pair<Vertex, Vertex> Edge;

/**
 * Operations graph. This corresponds to a control flow graph without basic blocks (but directly operations).
 */
class OpGraph final {
 public:
  /**
   * @return A unique pointer to a new empty operations graph
   */
  static std::unique_ptr<OpGraph> Create();

  static std::unique_ptr<OpGraph> FromControlFlowGraph(std::shared_ptr<ControlFlowGraph> cfg);

  /**
   * Create a new empty operations graph
   */
  OpGraph();

  /**
   * Delete the current operations graph.
   */
  ~OpGraph();

  void AddVertex(Vertex vertex);

  void AddEdge(Vertex source, Vertex target);

  void AddConditionalEdges(Vertex source, Vertex target_if_true,  Vertex target_if_false);

  bool HasVertex(Vertex node) const;

  bool HasEdge(Edge edge) const;

  std::unique_ptr<ControlFlowGraph> ToControlFlowGraph() const;

 private:
  /**
   * The set of vertices
   */
  std::set<Vertex> vertices_;

  /**
   * The set of edges
   */
  std::set<Edge> edges_;

  /**
   * A map from the source vertex to a pair <target_vertex, nullptr> if there is one out
   * edge or a pair <target_vertex_if_true, target_vertex_if_false> if there are two
   * out edges.
   */
  std::map<Vertex, std::unique_ptr<std::pair<Vertex, Vertex>>> out_edges_;

  /**
   * A map from the target vertex of the edge to the source vertex of the edge
   */
  std::map<Vertex, std::unique_ptr<std::set<Vertex>>> in_edges_;
};
} // namespace optimizer
} // namespace ir
} // namespace comp
