#include <comp/as/ast/instruction.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<Instruction> Instruction::Create(
  std::shared_ptr<Mnemonic> mnemonic,
  std::vector<std::shared_ptr<Operand>> operands) {
  return std::unique_ptr<Instruction>(new Instruction(mnemonic, operands));
}

Instruction::Instruction(
  std::shared_ptr<Mnemonic> mnemonic,
  std::vector<std::shared_ptr<Operand>> operands
) :
  Statement(Type::Instruction),
  mnemonic(mnemonic),
  operands(operands) {
}

Instruction::~Instruction() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
