#include <comp/as/arch/variables_table.h>

#include <comp/exceptions.h>

namespace comp {
namespace as {
namespace arch {
namespace x64 {
void VariablesTable::Register(
  std::shared_ptr<const ir::Variable> variable,
  std::shared_ptr<ast::MemoryReference> memory_reference
) {
  variables_[variable] = memory_reference;
}

std::shared_ptr<ast::MemoryReference> VariablesTable::Get(
  std::shared_ptr<const ir::Variable> variable
) {
  return variables_.at(variable);
}
bool VariablesTable::Contains(std::shared_ptr<const ir::Variable> variable) {
  return variables_.find(variable) != variables_.end();
}
}  // namespace x64
}  // namespace arch
}  // namespace as
}  // namespace comp
