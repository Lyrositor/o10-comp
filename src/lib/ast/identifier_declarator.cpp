#include <comp/ast/identifier_declarator.h>

namespace comp {
namespace ast {
std::unique_ptr<IdentifierDeclarator> IdentifierDeclarator::Create(
  std::shared_ptr<Identifier> identifier,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<IdentifierDeclarator>(
    new IdentifierDeclarator(identifier, location));
}

IdentifierDeclarator::IdentifierDeclarator(
  std::shared_ptr<Identifier> identifier,
  std::shared_ptr<SourceLocation> location
) : Declarator(Type::IdentifierDeclarator, location), identifier(identifier) {
}

IdentifierDeclarator::~IdentifierDeclarator() {
}
}  // namespace ast
}  // namespace comp
