#include <comp/ast/node.h>

namespace comp {
namespace ast {
Node::Node(Node::Type nodeType, std::shared_ptr<SourceLocation> location) :
    nodeType(nodeType), location(location) {
}

Node::~Node() {
}
}
}
