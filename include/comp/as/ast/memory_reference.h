#pragma once

#include <memory>
#include "comp/as/ast/operand.h"
#include "comp/as/ast/simple_operand.h"

namespace comp {
namespace as {
namespace ast {
/**
 * @see: https://sourceware.org/binutils/docs/as/i386_002dMemory.html#i386_002dMemory
 */
struct MemoryReference final : public Operand {
  std::unique_ptr<MemoryReference> Create(
    std::shared_ptr<SimpleOperand> base,
    std::shared_ptr<SimpleOperand> displacement = nullptr);

  std::unique_ptr<MemoryReference> Create(
    std::shared_ptr<SimpleOperand> base,
    std::shared_ptr<SimpleOperand> displacement,
    std::shared_ptr<SimpleOperand> index,
    size_t scale);

  MemoryReference(
    std::shared_ptr<SimpleOperand> base,
    std::shared_ptr<SimpleOperand> displacement,
    std::shared_ptr<SimpleOperand> index,
    size_t scale);

  ~MemoryReference();

  // void *section;
  std::shared_ptr<SimpleOperand> base;
  // Maybe it should be an int64_t
  std::shared_ptr<SimpleOperand> displacement;
  // Maybe it should be an int64_t
  std::shared_ptr<SimpleOperand> index;
  /**
   * One of: 1, 2, 4, 8
   */
  size_t scale;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
