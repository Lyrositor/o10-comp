#include <comp/ast/for_statement.h>

namespace comp {
namespace ast {
std::unique_ptr<ForStatement> ForStatement::Create(
  std::shared_ptr<Statement> initialization,
  std::shared_ptr<Statement> condition,
  std::shared_ptr<Statement> iteration,
  std::shared_ptr<Statement> loop,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<ForStatement>(
    new ForStatement(initialization, condition, iteration, loop, location));
}

ForStatement::ForStatement(
  std::shared_ptr<Statement> initialization,
  std::shared_ptr<Statement> condition,
  std::shared_ptr<Statement> iteration,
  std::shared_ptr<Statement> loop,
  std::shared_ptr<SourceLocation> location
) :
  Statement(Type::ForStatement, location),
  initialization(initialization),
  condition(condition),
  iteration(iteration),
  loop(loop) {
}

ForStatement::~ForStatement() {
}
}  // namespace ast
}  // namespace comp
