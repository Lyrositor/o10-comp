#include <comp/as/ast/type_directive.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<TypeDirective> TypeDirective::Create(
  std::shared_ptr<Symbol> symbol,
  TypeDescriptor type_descriptor) {
  return std::unique_ptr<TypeDirective>(new TypeDirective(symbol, type_descriptor));
}

TypeDirective::TypeDirective(
  std::shared_ptr<Symbol> symbol,
  TypeDescriptor type_descriptor
) :
  Directive(Type::TypeDirective),
  symbol(symbol),
  type_descriptor(type_descriptor) {
}

TypeDirective::~TypeDirective() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
