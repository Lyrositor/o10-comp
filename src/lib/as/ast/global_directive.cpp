#include <comp/as/ast/global_directive.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<GlobalDirective> GlobalDirective::Create(std::shared_ptr<Symbol> symbol) {
  return std::unique_ptr<GlobalDirective>(new GlobalDirective(symbol));
}

GlobalDirective::GlobalDirective(
  std::shared_ptr<Symbol> symbol
) :
  Directive(Type::GlobalDirective),
  symbol(symbol){
}

GlobalDirective::~GlobalDirective() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
