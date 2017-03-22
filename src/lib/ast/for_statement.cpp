#include <comp/ast/for_statement.h>

namespace comp {
namespace ast {
std::unique_ptr<ForStatement> ForStatement::Create(
  std::shared_ptr<RExpression> initialization,
  std::shared_ptr<RExpression> condition,
  std::shared_ptr<RExpression> iteration,
  std::shared_ptr<Statement> body,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<ForStatement>(
    new ForStatement(initialization, condition, iteration, body, location));
}

ForStatement::ForStatement(
  std::shared_ptr<Statement> initialization,
  std::shared_ptr<Statement> condition,
  std::shared_ptr<Statement> iteration,
  std::shared_ptr<Statement> body,
  std::shared_ptr<SourceLocation> location
) :
  Statement(Type::ForStatement, location),
  initialization(initialization),
  condition(condition),
  iteration(iteration),
  body(body) {
}

ForStatement::~ForStatement() {
}
}  // namespace ast
}  // namespace comp
