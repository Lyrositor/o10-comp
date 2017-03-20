#include <comp/as/ast/statement.h>

namespace comp {
namespace as {
namespace ast {
Statement::Statement(
  Type node_type,
  std::vector<std::shared_ptr<Symbol>> labels
) :
  Node(node_type),
  labels(labels) {
}

Statement::~Statement() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
