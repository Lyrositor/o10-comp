#include <comp/ast/statement.h>

namespace comp {
namespace ast {
Statement::Statement(Node::Type nodeType, std::shared_ptr<SourceLocation> location) :
  Node(nodeType, location) {
}

Statement::~Statement() {
}
}
}
