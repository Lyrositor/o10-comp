#include <comp/ast/node.h>

namespace comp {
namespace ast {
Node::Node(Type node_type, std::shared_ptr<SourceLocation> location) :
  node_type(node_type), location(location) {
}

Node::~Node() {
}
}  // namespace ast
}  // namespace comp
