#include <comp/as/ast/instruction.h>
#include <comp/as/ast/immediate_operand.h>
#include <comp/as/ast.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<Instruction> Instruction::Create(
  std::shared_ptr<Mnemonic> mnemonic,
  std::vector<std::shared_ptr<Operand>> operands
) {
  return std::unique_ptr<Instruction>(new Instruction(mnemonic, operands));
}

std::unique_ptr<Instruction> Instruction::Create(
  std::shared_ptr<Mnemonic> mnemonic,
  int64_t op1_value,
  std::shared_ptr<Operand> op2) {
  return Create(mnemonic, {ast::ImmediateOperand::Create(op1_value), op2});
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
