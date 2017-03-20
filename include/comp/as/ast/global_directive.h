#pragma once

#include <memory>
#include "comp/as/ast/directive.h"
#include "comp/as/ast/symbol.h"

namespace comp {
namespace as {
namespace ast {
/**
 * @see: https://sourceware.org/binutils/docs/as/Global.html#Global
 */
struct GlobalDirective final : public Directive {
  static std::unique_ptr<GlobalDirective> Create(std::shared_ptr<Symbol> symbol);

  GlobalDirective(std::shared_ptr<Symbol> symbol);

  ~GlobalDirective();

  std::shared_ptr<Symbol> symbol;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
