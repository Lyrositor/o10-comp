#pragma once

#include <comp/as/ast/memory_reference.h>
#include <comp/ir/variable.h>

#include <unordered_map>

namespace comp {
namespace as {
namespace arch {
namespace x64 {
class VariablesTable {
 public:
  void Register(
    std::shared_ptr<const ir::Variable> variable,
    std::shared_ptr<ast::MemoryReference> memory_reference);

  std::shared_ptr<ast::MemoryReference> Get(
    std::shared_ptr<const ir::Variable> variable);

  bool Contains(std::shared_ptr<const ir::Variable> variable);

 private:
  std::unordered_map<
  std::shared_ptr<const ir::Variable>,
  std::shared_ptr<ast::MemoryReference>> variables_;
};
}  // namespace x64
}  // namespace arch
}  // namespace as
}  // namespace comp
