#include <comp/ast/statement.h>

namespace comp {
namespace ast {
Statement::Statement(Type node_type, std::shared_ptr<SourceLocation> location) :
  Node(node_type, location) {
}

Statement::~Statement() {
}
}  // namespace ast
}  // namespace comp
