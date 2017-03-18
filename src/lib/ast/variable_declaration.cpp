#include <comp/ast/variable_declaration.h>

namespace comp {
namespace ast {
std::unique_ptr<VariableDeclaration> VariableDeclaration::Create(
  std::shared_ptr<DataType> data_type,
  std::vector<std::shared_ptr<VariableDeclarator>> declarators,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<VariableDeclaration>(
    new VariableDeclaration(data_type, declarators, location));
}

VariableDeclaration::VariableDeclaration(
  std::shared_ptr<DataType> data_type,
  std::vector<std::shared_ptr<VariableDeclarator>> declarators,
  std::shared_ptr<SourceLocation> location
) :
  Declaration(Type::VariableDeclaration, location),
  data_type(data_type),
  declarators(declarators) {
}

VariableDeclaration::~VariableDeclaration() {
}
}  // namespace ast
}  // namespace comp
