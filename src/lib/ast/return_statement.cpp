#include <comp/ast/expression.h>
#include <comp/ast/return_statement.h>

std::unique_ptr<comp::ast::ReturnStatement> comp::ast::ReturnStatement::Create(
  std::shared_ptr<comp::ast::Expression> expression,
  std::shared_ptr<comp::ast::SourceLocation> location
) {
  return std::unique_ptr<comp::ast::ReturnStatement>(
    new ReturnStatement(expression, location)
  );
}

comp::ast::ReturnStatement::ReturnStatement(
  std::shared_ptr<Expression> expression,
  std::shared_ptr<comp::ast::SourceLocation> location
) : Statement(Node::Type::ReturnStatement, location), expression(expression) {
}

comp::ast::ReturnStatement::~ReturnStatement() {
}

