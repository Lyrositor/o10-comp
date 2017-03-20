#include <comp/as/ast/mnemonic.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<Mnemonic> Mnemonic::Create(std::string name) {
  return std::unique_ptr<Mnemonic>(new Mnemonic(name));
}

Mnemonic::Mnemonic(
  std::string name
) :
  Node(Type::Mnemonic),
  name(name) {
}

Mnemonic::~Mnemonic() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
