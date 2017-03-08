#include <comp/ast/node.h>

namespace comp {
namespace ast {
Node::Node(Type type, std::shared_ptr<SourceLocation> location) :
  type(type), location(location) {
}

Node::~Node() {
}
}
}
