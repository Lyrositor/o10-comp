#include <comp/ast/null_statement.h>

namespace comp {
namespace ast {
std::unique_ptr<NullStatement> NullStatement::Create(
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<NullStatement>(new NullStatement(location));
}

NullStatement::NullStatement(std::shared_ptr<SourceLocation> location) :
  Statement(Type::NullStatement, location) {
}

NullStatement::~NullStatement() {
}
}  // namespace ast
}  // namespace comp
