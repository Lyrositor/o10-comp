#include <comp/as/ast/empty_statement.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<EmptyStatement> EmptyStatement::Create(
  std::vector<std::shared_ptr<Symbol>> labels) {
  return std::unique_ptr<EmptyStatement>(new EmptyStatement(labels));
}

EmptyStatement::EmptyStatement(
  std::vector<std::shared_ptr<Symbol>> labels
) :
  Statement(Type::EmptyStatement, labels) {
}

EmptyStatement::~EmptyStatement() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
