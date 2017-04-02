#include <comp/dot/ast/node.h>

namespace comp {
namespace dot {
namespace ast {
Node::Node(
  Type node_type
) :
  node_type(node_type) {
}

Node::~Node() {
}
}  // namespace ast
}  // namespace dot
}  // namespace comp
