#include <comp/dot/emit.h>
#include <cstdint>

namespace comp {
namespace dot {
void emitIdentifier(const std::string &identifier, std::ostream &out) {
  out << "\"";
  for(const char c : identifier) {
    switch (c) {
      case '\"': {
        out << "\\\"";
        break;
      }
      case '\\': {
        out << "\\\\";
        break;
      }
      case '\n': {
        out << "\\n";
        break;
      }
      default: {
        if (0x20 <= c && c <= 0x7e) {
          out << c;
        } else {
          out << "<?>";
        }
      }
    }
  }
  out << "\"";
}

void EmitAssignment(const ast::Assignment &node, std::ostream &out) {
  emitIdentifier(node.key, out);
  out << " = ";
  emitIdentifier(node.value, out);
}

void EmitEdgeStatement(const ast::EdgeStatement &node, std::ostream &out) {
  out << "E;";
}

void EmitAssignmentStatement(const ast::AssignmentStatement &node, std::ostream &out) {
  EmitAssignment(*node.assignment, out);
  out << ";";
}

void EmitGraph(const ast::Graph &node, std::ostream &out) {
  if (node.strict) {
    out << "strict ";
  }
  out << (node.directed ? "digraph " : "graph ");
  if (node.name != nullptr) {
    emitIdentifier(*node.name, out);
    out << " ";
  }
  out << "{";
  for (size_t i = 0, l = node.statements.size(); i < l; i++) {
    if (i == 0) {
      out << "\n";
    }
    auto statement = node.statements[i];
    EmitStatement(*statement, out);
    out << "\n";
  }
  out << "}";
}

void EmitNode(const ast::Node &node, std::ostream &out) {
  switch (node.node_type) {
    case ast::Node::Type::Assignment: {
      return EmitAssignment(static_cast<const ast::Assignment &>(node), out);
    }
    case ast::Node::Type::AssignmentStatement: {
      return EmitAssignmentStatement(static_cast<const ast::AssignmentStatement &>(node), out);
    }
    case ast::Node::Type::EdgeStatement: {
      return EmitEdgeStatement(static_cast<const ast::EdgeStatement &>(node), out);
    }
    case ast::Node::Type::Graph: {
      return EmitGraph(static_cast<const ast::Graph &>(node), out);
    }
    case ast::Node::Type::NodeStatement: {
      return EmitNodeStatement(static_cast<const ast::NodeStatement &>(node), out);
    }
    case ast::Node::Type::SubgraphStatement: {
      return EmitSubgraphStatement(static_cast<const ast::SubgraphStatement &>(node), out);
    }
    default: {
      throw std::domain_error("Unexpected value for `node.node_type`");
    }
  }
}

void EmitNodeStatement(const ast::NodeStatement &node, std::ostream &out) {
  out << "N;";
}

void EmitSubgraphStatement(const ast::SubgraphStatement &node, std::ostream &out) {
  out << "N;";
}

void EmitStatement(const ast::Statement &node, std::ostream &out) {
  EmitNode(node, out);
}
}  // namespace dot
}  // namespace comp
