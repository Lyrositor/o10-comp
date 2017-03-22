#include <comp/ast/declarator.h>

namespace comp {
namespace ast {
Declarator::Declarator(Type node_type, std::shared_ptr<SourceLocation> location)
  : Node(node_type, location) {
}

Declarator::~Declarator() {
}
}  // namespace ast
}  // namespace comp
