#include <comp/dot/ast/statement.h>

namespace comp {
namespace dot {
namespace ast {
Statement::Statement(
  Type node_type
) :
  Node(node_type) {
}

Statement::~Statement() {
}
}  // namespace ast
}  // namespace dot
}  // namespace comp
