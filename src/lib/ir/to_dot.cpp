#include <comp/ir/to_dot.h>

namespace comp {
namespace ir {
std::unique_ptr<dot::ast::Graph> ProgramToDot(const Program &node) {
  std::vector<std::shared_ptr<dot::ast::Statement>> body;

  for (auto symbol: node.GetSymbols()) {
    body.push_back(dot::ast::AssignmentStatement::Create(
      dot::ast::Assignment::Create("size", "4, 4")
    ));
  }

  return dot::ast::Graph::Create(true, true, nullptr, body);
}
}  // namespace ir
}  // namespace comp
