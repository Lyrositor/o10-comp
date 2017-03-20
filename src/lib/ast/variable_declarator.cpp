#include <comp/ast/variable_declarator.h>

namespace comp {
namespace ast {
std::unique_ptr<VariableDeclarator> VariableDeclarator::Create(
  std::shared_ptr<Declarator> declarator,
  std::shared_ptr<RExpression> initial_value,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<VariableDeclarator>(
    new VariableDeclarator(declarator, initial_value, location));
}

VariableDeclarator::VariableDeclarator(
  std::shared_ptr<Declarator> declarator,
  std::shared_ptr<RExpression> initial_value,
  std::shared_ptr<SourceLocation> location
) :
  Node(Type::VariableDeclarator, location),
  declarator(declarator),
  initial_value(initial_value) {
}

VariableDeclarator::~VariableDeclarator() {
}
}  // namespace ast
}  // namespace comp
