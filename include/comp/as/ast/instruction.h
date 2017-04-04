#pragma once

#include <memory>
#include <string>
#include <vector>

#include "comp/as/ast/mnemonic.h"
#include "comp/as/ast/operand.h"
#include "comp/as/ast/statement.h"

namespace comp {
namespace as {
namespace ast {
struct Instruction final : public Statement {
  static std::unique_ptr<Instruction> Create(
    std::shared_ptr<Mnemonic> mnemonic,
    std::vector<std::shared_ptr<Operand>> operands = {});

  static std::unique_ptr<Instruction> Create(
    std::shared_ptr<Mnemonic> mnemonic,
    int64_t op1_value,
    std::shared_ptr<Operand> op2);

  Instruction(
    std::shared_ptr<Mnemonic> mnemonic,
    std::vector<std::shared_ptr<Operand>> operands);

  ~Instruction();

  std::shared_ptr<Mnemonic> mnemonic;
  std::vector<std::shared_ptr<Operand>> operands;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
