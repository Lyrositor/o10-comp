#pragma once

#include <memory>
#include <string>
#include "comp/as/ast/node.h"

namespace comp {
namespace as {
namespace ast {
struct Mnemonic final : public Node {
  std::unique_ptr<Mnemonic> Create(std::string name);

  Mnemonic(std::string name);

  ~Mnemonic();

  std::string name;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
