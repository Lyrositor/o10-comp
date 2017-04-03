#include <comp/as/ast/size_directive.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<SizeDirective> SizeDirective::Create(
  std::shared_ptr<Symbol> symbol,
  std::shared_ptr<AddressExpression> size) {
  return std::unique_ptr<SizeDirective>(new SizeDirective(symbol, size));
}

SizeDirective::SizeDirective(
  std::shared_ptr<Symbol> symbol,
  std::shared_ptr<AddressExpression> size
) :
  Directive(Type::SizeDirective),
  symbol(symbol),
  size(size) {
}

SizeDirective::~SizeDirective() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
