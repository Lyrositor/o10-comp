#include <comp/ir/program.h>

namespace comp {
namespace ir {
Program::Program() {
}

Program::~Program() {
}

void Program::AddSymbol(std::shared_ptr<const ProgramSymbol> symbol) {
  symbols_.push_back(symbol);
}

std::vector<std::shared_ptr<const ProgramSymbol>> Program::GetSymbols() const {
  return symbols_;
}
}  // namespace ir
}  // namespace comp
