#include <comp/ast/expression_statement.h>

namespace comp {
namespace ast {
std::unique_ptr<ExpressionStatement> ExpressionStatement::Create(
  std::shared_ptr<RExpression> expression,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<ExpressionStatement>(
    new ExpressionStatement(expression, location));
}

ExpressionStatement::ExpressionStatement(
  std::shared_ptr<RExpression> expression,
  std::shared_ptr<SourceLocation> location
) : Statement(Type::ExpressionStatement, location), expression(expression) {
}

ExpressionStatement::~ExpressionStatement() {
}
}  // namespace ast
}  // namespace comp
