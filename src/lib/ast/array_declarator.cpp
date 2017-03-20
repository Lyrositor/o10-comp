#include <comp/ast/array_declarator.h>

namespace comp {
namespace ast {
std::unique_ptr<ArrayDeclarator> ArrayDeclarator::Create(
  std::shared_ptr<RExpression> size,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<ArrayDeclarator>(new ArrayDeclarator(size, location));
}

ArrayDeclarator::ArrayDeclarator(
  std::shared_ptr<RExpression> size,
  std::shared_ptr<SourceLocation> location
) :
  Declarator(Type::ArrayDeclarator, location),
  size(size) {
}

ArrayDeclarator::~ArrayDeclarator() {
}
}  // namespace ast
}  // namespace comp
