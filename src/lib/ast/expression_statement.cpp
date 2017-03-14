#include <comp/ast/expression_statement.h>
#include <memory>

namespace comp {
namespace ast {
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
