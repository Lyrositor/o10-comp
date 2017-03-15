#include <comp/ast/variable_declaration.h>
#include <comp/ast/data_type.h>

namespace comp {
namespace ast {
std::unique_ptr<VariableDeclaration> VariableDeclaration::Create(
  std::shared_ptr<DataType> dataType,
  std::vector<std::shared_ptr<VariableDeclarator>> declarators,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<VariableDeclaration>(new VariableDeclaration(dataType, declarators, location));
}

VariableDeclaration::VariableDeclaration(
  std::shared_ptr<DataType> dataType,
  std::vector<std::shared_ptr<VariableDeclarator>> declarators,
  std::shared_ptr<SourceLocation> location
) :
  Declaration(Node::Type::VariableDeclaration, location),
  dataType(dataType),
  declarators(declarators) {
}

VariableDeclaration::~VariableDeclaration() {
}
}
}
