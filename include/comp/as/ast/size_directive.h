#pragma once

#include <memory>
#include "comp/as/ast/directive.h"
#include "comp/as/ast/address_expression.h"
#include "comp/as/ast/symbol.h"

namespace comp {
namespace as {
namespace ast {
/**
 * @see: https://sourceware.org/binutils/docs/as/Size.html#Size
 */
struct SizeDirective final : public Directive {
  static std::unique_ptr<SizeDirective> Create(
      std::shared_ptr<Symbol> symbol,
      std::shared_ptr<AddressExpression> size);

  SizeDirective(
      std::shared_ptr<Symbol> symbol,
      std::shared_ptr<AddressExpression> size);

  ~SizeDirective();

  std::shared_ptr<Symbol> symbol;
  std::shared_ptr<AddressExpression> size;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
