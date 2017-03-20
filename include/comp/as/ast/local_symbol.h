#pragma once

#include <memory>
#include "comp/as/ast/symbol.h"

namespace comp {
namespace as {
namespace ast {
/**
 * @see: https://sourceware.org/binutils/docs/as/Symbol-Names.html#Symbol-Names
 */
struct LocalSymbol final : public Symbol {
  std::unique_ptr<LocalSymbol> Create(std::string name);

  LocalSymbol(std::string name);

  ~LocalSymbol();

  std::string name;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
