#include <comp/as/ast/local_symbol.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<LocalSymbol> LocalSymbol::Create(std::string name) {
  return std::unique_ptr<LocalSymbol>(new LocalSymbol(name));
}

LocalSymbol::LocalSymbol(
  std::string name
) :
  Symbol(Type::LocalSymbol),
  name(name) {
}

LocalSymbol::~LocalSymbol() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
