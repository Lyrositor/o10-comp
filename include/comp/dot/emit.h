#pragma once

#include <ostream>
#include "comp/dot/ast.h"

namespace comp {
namespace dot {
void EmitAssignment(const ast::Assignment &node, std::ostream &out);
void EmitAssignmentStatement(const ast::AssignmentStatement &node, std::ostream &out);
void EmitEdgeStatement(const ast::EdgeStatement &node, std::ostream &out);
void EmitGraph(const ast::Graph &node, std::ostream &out);
void EmitNode(const ast::Node &node, std::ostream &out);
void EmitNodeStatement(const ast::NodeStatement &node, std::ostream &out);
void EmitStatement(const ast::Statement &node, std::ostream &out);
void EmitSubgraphStatement(const ast::SubgraphStatement &node, std::ostream &out);
}  // namespace dot
}  // namespace comp
