#include <comp/dot/emit.h>

namespace comp {
namespace dot {
void emitIdentifier(const std::string &identifier, std::ostream &out) {
  out << identifier;
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
  out << "}";
}
}  // namespace dot
}  // namespace comp
