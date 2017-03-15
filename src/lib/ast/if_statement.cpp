#include <comp/ast/if_statement.h>
#include <memory>

namespace comp {
namespace ast {
std::unique_ptr<IfStatement> IfStatement::Create(
  std::shared_ptr<Expression> test,
  std::shared_ptr<Statement> consequence,
  std::shared_ptr<Statement> alternative,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<IfStatement>(new IfStatement(test, consequence, alternative, location));
}

IfStatement::IfStatement(
  std::shared_ptr<Expression> test,
  std::shared_ptr<Statement> consequence,
  std::shared_ptr<Statement> alternative,
  std::shared_ptr<SourceLocation> location
) :
  Statement(Node::Type::IfStatement, location),
  test(test),
  consequence(consequence),
  alternative(alternative) {
}

IfStatement::~IfStatement() {
}
}
}
