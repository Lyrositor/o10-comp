#pragma once

#include <memory>
#include <vector>

#include "comp/ir/program_symbol.h"

namespace comp {
namespace ir {
class Program {
 public:
  Program();

  ~Program();

  void AddSymbol(std::shared_ptr<ProgramSymbol> symbol);

 protected:
  std::vector<std::shared_ptr<ProgramSymbol>> symbols_;
};
}  // namespace ir
}  // namespace comp
