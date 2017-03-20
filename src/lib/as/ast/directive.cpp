#include <comp/as/ast/directive.h>

namespace comp {
namespace as {
namespace ast {
Directive::Directive(
  Type node_type,
  std::vector<std::shared_ptr<Symbol>> labels
) :
  Statement(node_type, labels) {
}

Directive::~Directive() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
