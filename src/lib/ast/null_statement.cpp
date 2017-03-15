#include <comp/ast/null_statement.h>

namespace comp {
namespace ast {
std::unique_ptr<comp::ast::NullStatement> comp::ast::NullStatement::Create(
  std::shared_ptr<comp::ast::SourceLocation> location
) {
  return std::unique_ptr<comp::ast::NullStatement>(
    new NullStatement(location)
  );
}

comp::ast::NullStatement::NullStatement(
  std::shared_ptr<comp::ast::SourceLocation> location
) : Statement(Node::Type::NullStatement, location) {
}

comp::ast::NullStatement::~NullStatement() {
}
}
}
