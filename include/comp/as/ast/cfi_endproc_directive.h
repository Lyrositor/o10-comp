#pragma once

#include <memory>
#include "comp/as/ast/directive.h"

namespace comp {
namespace as {
namespace ast {
/**
 * @see: https://sourceware.org/binutils/docs/as/CFI-directives.html#CFI-directives
 */
struct CfiEndprocDirective final : public Directive {
  static std::unique_ptr<CfiEndprocDirective> Create();

  CfiEndprocDirective();

  ~CfiEndprocDirective();
};
}  // namespace ast
}  // namespace as
}  // namespace comp
