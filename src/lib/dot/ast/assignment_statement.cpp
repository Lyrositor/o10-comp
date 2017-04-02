#include <comp/dot/ast/assignment_statement.h>

namespace comp {
namespace dot {
namespace ast {
std::unique_ptr<AssignmentStatement> AssignmentStatement::Create(
  std::shared_ptr<Assignment> assignment
) {
  return std::unique_ptr<AssignmentStatement>(new AssignmentStatement(assignment));
}

AssignmentStatement::AssignmentStatement(
  std::shared_ptr<Assignment> assignment
) :
  Statement(Type::AssignmentStatement),
  assignment(assignment) {
}

AssignmentStatement::~AssignmentStatement() {
}
}  // namespace ast
}  // namespace dot
}  // namespace comp
