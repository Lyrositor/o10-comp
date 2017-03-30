#pragma once

#include <memory>
#include "comp/as/ast/directive.h"

namespace comp {
namespace as {
namespace ast {
/**
 * @see: https://sourceware.org/binutils/docs/as/CFI-directives.html#CFI-directives
 */
struct CfiDefCfaOffsetDirective final : public Directive {
  static std::unique_ptr<CfiDefCfaOffsetDirective> Create(
    std::shared_ptr<Expression> offset);

  CfiDefCfaOffsetDirective(
    std::shared_ptr<Expression> offset);

  ~CfiDefCfaOffsetDirective();

  std::shared_ptr<Expression> offset;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
