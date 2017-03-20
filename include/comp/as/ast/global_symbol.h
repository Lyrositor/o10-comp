#pragma once

#include <memory>
#include <string>
#include "comp/as/ast/symbol.h"

namespace comp {
namespace as {
namespace ast {
/**
 * A symbol that is exported in the object file, as opposed to a local symbol.
 *
 * @see: https://sourceware.org/binutils/docs/as/Symbol-Names.html#Symbol-Names
 */
struct GlobalSymbol final : public Symbol {
  std::unique_ptr<GlobalSymbol> Create(std::string name);

  /**
   * @param name Name of the label
   */
  GlobalSymbol(std::string name);

  ~GlobalSymbol();

  std::string name;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
