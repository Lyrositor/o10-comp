#pragma once

#include <memory>
#include "comp/as/ast/directive.h"
#include "comp/as/ast/symbol.h"

namespace comp {
namespace as {
namespace ast {
enum class TypeDescriptor {
  FUNCTION,
  INDIRECT_FUNCTION,
  DATA_OBJECT,
  THREAD_LOCAL_DATA_OBJECT,
  COMMON_DATA_OBJECT,
  NO_TYPE,
  UNIQUE_DATA_OBJECT
};

/**
 * @see: https://sourceware.org/binutils/docs/as/Type.html#Type
 */
struct TypeDirective final : public Directive {
  static std::unique_ptr<TypeDirective> Create(
    std::shared_ptr<Symbol> symbol,
    TypeDescriptor type_descriptor);

  TypeDirective(
      std::shared_ptr<Symbol> symbol,
      TypeDescriptor type_descriptor);

  ~TypeDirective();

  std::shared_ptr<Symbol> symbol;
  TypeDescriptor type_descriptor;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
