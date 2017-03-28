#pragma once

#include <memory>
#include "comp/as/ast/directive.h"
#include "comp/as/ast/expression.h"
#include "comp/as/ast/register_operand.h"

namespace comp {
namespace as {
namespace ast {
/**
 * @see: https://sourceware.org/binutils/docs/as/CFI-directives.html#CFI-directives
 */
struct CfiOffsetDirective final : public Directive {
  static std::unique_ptr<CfiOffsetDirective> Create(
    std::shared_ptr<RegisterOperand> reg,
    std::shared_ptr<Expression> size);

  CfiOffsetDirective(
    std::shared_ptr<RegisterOperand> reg,
    std::shared_ptr<Expression> size);

  ~CfiOffsetDirective();

  std::shared_ptr<RegisterOperand> reg;
  std::shared_ptr<Expression> size;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
