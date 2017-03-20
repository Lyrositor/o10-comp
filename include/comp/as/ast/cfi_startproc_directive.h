#pragma once

#include <memory>
#include "comp/as/ast/directive.h"

namespace comp {
namespace as {
namespace ast {
/**
 * @see: https://sourceware.org/binutils/docs/as/CFI-directives.html#CFI-directives
 */
struct CfiStartprocDirective final : public Directive {
  static std::unique_ptr<CfiStartprocDirective> Create();

  CfiStartprocDirective();

  ~CfiStartprocDirective();
};
}  // namespace ast
}  // namespace as
}  // namespace comp
