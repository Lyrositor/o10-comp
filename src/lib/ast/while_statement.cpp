#include <comp/ast/while_statement.h>

namespace comp {
namespace ast {
std::unique_ptr<WhileStatement> WhileStatement::Create(
  std::shared_ptr<RExpression> condition,
  std::shared_ptr<Statement> loop,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<WhileStatement>(
    new WhileStatement(condition, loop, location));
}

WhileStatement::WhileStatement(
  std::shared_ptr<RExpression> condition,
  std::shared_ptr<Statement> loop,
  std::shared_ptr<SourceLocation> location
) :
  Statement(Type::WhileStatement, location),
  condition(condition),
  loop(loop) {
}

WhileStatement::~WhileStatement() {
}
}  // namespace ast
}  // namespace comp
