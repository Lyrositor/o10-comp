#pragma once

#include <memory>
#include <string>
#include "comp/as/ast/simple_operand.h"

namespace comp {
namespace as {
namespace ast {
struct RegisterOperand final : public SimpleOperand {
  std::unique_ptr<RegisterOperand> Create(std::string name);

  RegisterOperand(std::string name);

  ~RegisterOperand();

  std::string name;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
