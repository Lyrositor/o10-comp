#include <comp/ir/program.h>

namespace comp {
namespace ir {
Program::Program() {
}

Program::~Program() {
}

void Program::AddSymbol(std::shared_ptr<ProgramSymbol> symbol) {
  symbols_.push_back(symbol);
}
}  // namespace ir
}  // namespace comp
