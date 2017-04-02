#include <comp/dot/ast/edge_statement.h>

namespace comp {
namespace dot {
namespace ast {
std::unique_ptr<EdgeStatement> EdgeStatement::Create(
  std::vector<std::string> nodes,
  std::vector<std::shared_ptr<Assignment>> attributes
) {
  return std::unique_ptr<EdgeStatement>(new EdgeStatement(nodes, attributes));
}

EdgeStatement::EdgeStatement(
  std::vector<std::string> nodes,
  std::vector<std::shared_ptr<Assignment>> attributes
) :
  Statement(Type::EdgeStatement),
  nodes(nodes),
  attributes(attributes) {
}

EdgeStatement::~EdgeStatement() {
}
}  // namespace ast
}  // namespace dot
}  // namespace comp
