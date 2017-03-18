#include <comp/ast/identifier.h>

namespace comp {
namespace ast {
std::unique_ptr<Identifier> Identifier::Create(
  std::string name,
  std::shared_ptr<SourceLocation> location) {
  return std::unique_ptr<Identifier>(new Identifier(name, location));
}

Identifier::Identifier(
  std::string name,
  std::shared_ptr<SourceLocation> location
) :
  LExpression(Type::Identifier, location),
  RExpression(Type::Identifier, location),
  name(name){
}

Identifier::~Identifier() {
}
}  // namespace ast
}  // namespace comp
