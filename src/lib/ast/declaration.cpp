#include <comp/ast/declaration.h>

namespace comp {
namespace ast {
Declaration::Declaration(
  Type node_type,
  std::shared_ptr<SourceLocation> location
) : Statement(node_type, location) {
}

Declaration::~Declaration() {
}
}  // namespace ast
}  // namespace comp

