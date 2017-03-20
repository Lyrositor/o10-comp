#pragma once

#include <memory>
#include "comp/as/ast/directive.h"

namespace comp {
namespace as {
namespace ast {
/**
 * @see: https://sourceware.org/binutils/docs/as/Text.html#Text
 */
struct TextDirective final : public Directive {
  std::unique_ptr<TextDirective> Create(size_t subsection = 0);

  TextDirective(size_t subsection = 0);

  ~TextDirective();

  size_t subsection;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
