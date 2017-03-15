#include <comp/ast/expression_statement.h>
#include <memory>

namespace comp {
namespace ast {
std::unique_ptr<ExpressionStatement> ExpressionStatement::Create(
  std::shared_ptr<Expression> expression,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<ExpressionStatement>(new ExpressionStatement(expression, location));
}

ExpressionStatement::ExpressionStatement(
  std::shared_ptr<Expression> expression,
  std::shared_ptr<SourceLocation> location
) :
  Statement(Node::Type::ExpressionStatement, location),
  expression(expression) {
}

ExpressionStatement::~ExpressionStatement() {
}
}
}
