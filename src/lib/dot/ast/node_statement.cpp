#include <comp/dot/ast/node_statement.h>

namespace comp {
namespace dot {
namespace ast {
std::unique_ptr<NodeStatement> NodeStatement::Create(
  std::string id,
  std::vector<std::shared_ptr<Assignment>> attributes
) {
  return std::unique_ptr<NodeStatement>(new NodeStatement(id, attributes));
}

NodeStatement::NodeStatement(
  std::string id,
  std::vector<std::shared_ptr<Assignment>> attributes
) :
  Statement(Type::NodeStatement),
  id(id),
  attributes(attributes) {
}

NodeStatement::~NodeStatement() {
}
}  // namespace ast
}  // namespace dot
}  // namespace comp
