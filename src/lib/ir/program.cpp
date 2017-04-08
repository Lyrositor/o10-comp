#include <comp/ir/program.h>

namespace comp {
namespace ir {
std::unique_ptr<Program> Program::Create() {
  return std::unique_ptr<Program>(new Program());
}

Program::Program() {
}

Program::~Program() {
}

void Program::AddSymbol(std::shared_ptr<const ProgramSymbol> symbol) {
  symbols_.push_back(symbol);
}

std::vector<std::shared_ptr<const ProgramSymbol>> Program::GetSymbols() const {
  return std::vector<std::shared_ptr<const ProgramSymbol>>(symbols_.begin(), symbols_.end());
}
}  // namespace ir
}  // namespace comp
