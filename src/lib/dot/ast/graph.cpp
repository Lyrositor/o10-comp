#include <comp/dot/ast/graph.h>

namespace comp {
namespace dot {
namespace ast {
std::unique_ptr<Graph> Graph::Create(
  bool strict,
  bool directed,
  std::shared_ptr<std::string> name,
  std::vector<std::shared_ptr<Statement>> statements
) {
  return std::unique_ptr<Graph>(new Graph(strict, directed, name, statements));
}

Graph::Graph(
  bool strict,
  bool directed,
  std::shared_ptr<std::string> name,
  std::vector<std::shared_ptr<Statement>> statements
) :
  Node(Type::Graph),
  strict(strict),
  directed(directed),
  name(name),
  statements(statements) {
}

Graph::~Graph() {
}
}  // namespace ast
}  // namespace dot
}  // namespace comp
