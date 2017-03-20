#include <comp/as/ast/register_operand.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<RegisterOperand> RegisterOperand::Create(std::string name) {
  return std::unique_ptr<RegisterOperand>(new RegisterOperand(name));
}

RegisterOperand::RegisterOperand(
  std::string name
) :
  SimpleOperand(Type::RegisterOperand),
  name(name) {
}

RegisterOperand::~RegisterOperand() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
