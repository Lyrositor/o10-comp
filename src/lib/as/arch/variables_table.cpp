#include <comp/as/arch/variables_table.h>

namespace comp {
namespace as {
namespace arch {
void VariablesTable::Register(
  std::shared_ptr<const ir::Variable> variable,
  std::shared_ptr<ast::MemoryReference> memory_reference
) {
  variables_[variable] = memory_reference;
}

std::shared_ptr<ast::MemoryReference> VariablesTable::Get(
  std::shared_ptr<const ir::Variable> variable
) const {
  return variables_.at(variable);
}

bool VariablesTable::Contains(
  std::shared_ptr<const ir::Variable> variable
) const {
  return variables_.find(variable) != variables_.end();
}
}  // namespace arch
}  // namespace as
}  // namespace comp
