#include <gtest/gtest.h>

#include <comp/ir/optimizer/op_graph.h>

namespace comp {
namespace ir {
namespace optimizer {
TEST(comp__ir__optimizer__op_graph, AddEdge) {
  auto graph = OpGraph::Create();
  Vertex v1 = NoOp::Create();
  Vertex v2 = NoOp::Create();
  Edge e = Edge(v1, v2);
  ASSERT_FALSE(graph->HasVertex(v1));
  ASSERT_FALSE(graph->HasVertex(v2));
  ASSERT_FALSE(graph->HasEdge(e));
  graph->AddVertex(v1);
  ASSERT_TRUE(graph->HasVertex(v1));
  ASSERT_FALSE(graph->HasVertex(v2));
  ASSERT_FALSE(graph->HasEdge(e));
  graph->AddVertex(v2);
  ASSERT_TRUE(graph->HasVertex(v1));
  ASSERT_TRUE(graph->HasVertex(v2));
  ASSERT_FALSE(graph->HasEdge(e));
  graph->AddEdge(v1, v2);
  ASSERT_TRUE(graph->HasVertex(v1));
  ASSERT_TRUE(graph->HasVertex(v2));
  ASSERT_TRUE(graph->HasEdge(e));
  std::set<Vertex> v1_in_edges = graph->GetInEdges(v1);
  std::set<Vertex> v2_in_edges = graph->GetInEdges(v2);
  ASSERT_TRUE(v1_in_edges.size() == 0);
  ASSERT_TRUE(v2_in_edges.size() == 1);
  std::pair<Vertex, Vertex> actual_v1_out_edges = graph->GetOutEdges(v1);
  std::pair<Vertex, Vertex> actual_v2_out_edges = graph->GetOutEdges(v2);
  std::pair<Vertex, Vertex> expected_v1_out_edges(v2, nullptr);
  std::pair<Vertex, Vertex> expected_v2_out_edges(nullptr, nullptr);
  ASSERT_EQ(actual_v1_out_edges, expected_v1_out_edges);
  ASSERT_EQ(actual_v2_out_edges, expected_v2_out_edges);
}

TEST(comp__ir__build_ir, AddEdgeNoVertices) {
  auto graph = OpGraph::Create();
  Vertex v1 = NoOp::Create();
  Vertex v2 = NoOp::Create();
  Edge e = Edge(v1, v2);
  ASSERT_THROW(graph->AddEdge(v1, v2);, std::runtime_error);
}

TEST(comp__ir__build_ir, AddEdgeNoTarget) {
  auto graph = OpGraph::Create();
  Vertex v1 = NoOp::Create();
  Vertex v2 = NoOp::Create();
  Edge e = Edge(v1, v2);
  graph->AddVertex(v1);
  ASSERT_THROW(graph->AddEdge(v1, v2);, std::runtime_error);
}

TEST(comp__ir__build_ir, AddEdgeNoSource) {
  auto graph = OpGraph::Create();
  Vertex v1 = NoOp::Create();
  Vertex v2 = NoOp::Create();
  Edge e = Edge(v1, v2);
  graph->AddVertex(v2);
  ASSERT_THROW(graph->AddEdge(v1, v2);, std::runtime_error);
}
}  // namespace optimizer
}  // namespace ir
}  // namespace comp
