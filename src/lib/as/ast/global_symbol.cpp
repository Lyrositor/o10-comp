#include <comp/as/ast/global_symbol.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<GlobalSymbol> GlobalSymbol::Create(std::string name) {
  return std::unique_ptr<GlobalSymbol>(new GlobalSymbol(name));
}

GlobalSymbol::GlobalSymbol(
  std::string name
) :
  Symbol(Type::GlobalSymbol),
  name(name) {
}

GlobalSymbol::~GlobalSymbol() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
