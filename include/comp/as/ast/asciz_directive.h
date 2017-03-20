#pragma once

#include <memory>
#include <string>
#include "comp/as/ast/directive.h"
#include "comp/as/ast/expression.h"

namespace comp {
namespace as {
namespace ast {
/**
 * @see: https://sourceware.org/binutils/docs/as/Asciz.html#Asciz
 */
struct AscizDirective final : public Directive {
  std::unique_ptr<AscizDirective> Create(std::string value);

  AscizDirective(std::string value);

  ~AscizDirective();

  std::string value;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
