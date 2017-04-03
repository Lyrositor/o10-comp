#include <comp/as/ast/memory_reference.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<MemoryReference> MemoryReference::Create(
  std::shared_ptr<SimpleOperand> base,
  std::shared_ptr<AddressExpression> displacement) {
  return std::unique_ptr<MemoryReference>(new MemoryReference(base, displacement, nullptr, 1));
}

std::unique_ptr<MemoryReference> MemoryReference::Create(
  std::shared_ptr<SimpleOperand> base,
  std::shared_ptr<AddressExpression> displacement,
  std::shared_ptr<AddressExpression> index,
  size_t scale) {
  return std::unique_ptr<MemoryReference>(new MemoryReference(base, displacement, index, scale));
}

MemoryReference::MemoryReference(
  std::shared_ptr<SimpleOperand> base,
  std::shared_ptr<AddressExpression> displacement,
  std::shared_ptr<AddressExpression> index,
  size_t scale
) :
  Operand(Type::MemoryReference),
  base(base),
  displacement(displacement),
  index(index),
  scale(scale) {
}

MemoryReference::~MemoryReference() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
