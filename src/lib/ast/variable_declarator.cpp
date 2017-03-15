#include <comp/ast/variable_declarator.h>
#include <comp/ast/data_type.h>

namespace comp {
namespace ast {
std::unique_ptr<VariableDeclarator> VariableDeclarator::Create(
  std::shared_ptr<Identifier> identifier,
  std::shared_ptr<Expression> initial_value,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<VariableDeclarator>(new VariableDeclarator(identifier, initial_value, location));
}

VariableDeclarator::VariableDeclarator(
  std::shared_ptr<Identifier> identifier,
  std::shared_ptr<Expression> initial_value,
  std::shared_ptr<SourceLocation> location
) :
  Node(Node::Type::VariableDeclarator, location),
  identifier(identifier),
  initial_value(initial_value) {
}

VariableDeclarator::~VariableDeclarator() {
}
}
}
