#include <comp/as/ast/node.h>

namespace comp {
namespace as {
namespace ast {
Node::Node(
  Type node_type
) :
  node_type(node_type) {
}

Node::~Node() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
