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

  void AddEdge(Edge edge);

  bool HasVertex(Vertex node) const;

  bool HasEdge(Edge edge) const;

  std::unique_ptr<ControlFlowGraph> ToControlFlowGraph() const;

 private:
  /**
   * The set of vertices
   */
  std::set<Vertex> vertices;

  /**
   * The set of edges
   */
  std::set<Edge> edges;

  /**
   * A map from the source vertex of the edge to the target vertex of the edge
   */
  std::map<Vertex, std::unique_ptr<std::set<Vertex>>> out_edges;

  /**
   * A map from the target vertex of the edge to the source vertex of the edge
   */
  std::map<Vertex, std::unique_ptr<std::set<Vertex>>> in_edges;
};
} // namespace optimizer
} // namespace ir
} // namespace comp
