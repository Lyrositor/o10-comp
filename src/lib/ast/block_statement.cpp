#include <comp/ast/block_statement.h>
#include <memory>

namespace comp {
namespace ast {
BlockStatement::BlockStatement(
  std::vector<std::shared_ptr<Statement>> body,
  std::shared_ptr<SourceLocation> location
) :
  Statement(Node::Type::BlockStatement, location),
  body(body) {
}

BlockStatement::~BlockStatement() {
}
}
}
