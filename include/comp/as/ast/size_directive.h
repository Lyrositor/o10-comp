#pragma once

#include <memory>
#include "comp/as/ast/directive.h"
#include "comp/as/ast/expression.h"
#include "comp/as/ast/symbol.h"

namespace comp {
namespace as {
namespace ast {
/**
 * @see: https://sourceware.org/binutils/docs/as/Size.html#Size
 */
struct SizeDirective final : public Directive {
  std::unique_ptr<SizeDirective> Create(
      std::shared_ptr<Symbol> symbol,
      std::shared_ptr<Expression> size);

  SizeDirective(
      std::shared_ptr<Symbol> symbol,
      std::shared_ptr<Expression> size);

  ~SizeDirective();

  std::shared_ptr<Symbol> symbol;
  std::shared_ptr<Expression> size;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
