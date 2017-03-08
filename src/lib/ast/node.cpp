#include <comp/ast/node.h>

namespace comp {
namespace ast {
Node::Node(NodeType type_, std::shared_ptr<SourceLocation> location_) :
    type(type_), location(location_) {}
Node::~Node() {}
}
}
