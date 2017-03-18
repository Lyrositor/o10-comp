#include <comp/ast/return_statement.h>

namespace comp {
namespace ast {
std::unique_ptr<ReturnStatement> ReturnStatement::Create(
  std::shared_ptr<RExpression> expression,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<ReturnStatement>(
    new ReturnStatement(expression, location)
  );
}

ReturnStatement::ReturnStatement(
  std::shared_ptr<RExpression> expression,
  std::shared_ptr<SourceLocation> location
) : Statement(Type::ReturnStatement, location), expression(expression) {
}

ReturnStatement::~ReturnStatement() {
}
}  // namespace ast
}  // namespace comp
