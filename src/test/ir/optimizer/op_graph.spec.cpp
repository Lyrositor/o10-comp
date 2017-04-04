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
  graph->AddEdge(e);
  ASSERT_TRUE(graph->HasVertex(v1));
  ASSERT_TRUE(graph->HasVertex(v2));
  ASSERT_TRUE(graph->HasEdge(e));
}

TEST(comp__ir__build_ir, AddEdgeNoVertices) {
  auto graph = OpGraph::Create();
  Vertex v1 = NoOp::Create();
  Vertex v2 = NoOp::Create();
  Edge e = Edge(v1, v2);
  ASSERT_THROW(graph->AddEdge(e);, std::runtime_error);
}

TEST(comp__ir__build_ir, AddEdgeNoTarget) {
  auto graph = OpGraph::Create();
  Vertex v1 = NoOp::Create();
  Vertex v2 = NoOp::Create();
  Edge e = Edge(v1, v2);
  graph->AddVertex(v1);
  ASSERT_THROW(graph->AddEdge(e);, std::runtime_error);
}

TEST(comp__ir__build_ir, AddEdgeNoSource) {
  auto graph = OpGraph::Create();
  Vertex v1 = NoOp::Create();
  Vertex v2 = NoOp::Create();
  Edge e = Edge(v1, v2);
  graph->AddVertex(v2);
  ASSERT_THROW(graph->AddEdge(e);, std::runtime_error);
}
}  // namespace optimizer
}  // namespace ir
}  // namespace comp
