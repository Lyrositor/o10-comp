#include <comp/dot/ast/subgraph_statement.h>

namespace comp {
namespace dot {
namespace ast {
std::unique_ptr<SubgraphStatement> SubgraphStatement::Create(
  std::shared_ptr<std::string> name,
  std::vector<std::shared_ptr<std::string>> statements
) {
  return std::unique_ptr<SubgraphStatement>(new SubgraphStatement(name, statements));
}

SubgraphStatement::SubgraphStatement(
  std::shared_ptr<std::string> name,
  std::vector<std::shared_ptr<std::string>> statements
) :
  Statement(Type::SubgraphStatement),
  name(name),
  statements(statements) {
}

SubgraphStatement::~SubgraphStatement() {
}
}  // namespace ast
}  // namespace dot
}  // namespace comp
