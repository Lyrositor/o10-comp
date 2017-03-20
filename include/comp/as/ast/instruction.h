#pragma once

#include <memory>
#include <vector>
#include "comp/as/ast/statement.h"
#include "comp/as/ast/mnemonic.h"
#include "comp/as/ast/operand.h"

namespace comp {
namespace as {
namespace ast {
struct Instruction final : public Statement {
  std::unique_ptr<Instruction> Create(
      std::shared_ptr<Mnemonic> mnemonic,
      std::vector<std::shared_ptr<Operand>> operands);

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
