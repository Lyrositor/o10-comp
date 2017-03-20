#pragma once

#include <memory>
#include <vector>
#include "comp/as/ast/directive.h"

namespace comp {
namespace as {
namespace ast {
/**
 * @see: https://sourceware.org/binutils/docs/as/Quad.html#Quad
 */
struct QuadDirective final : public Directive {
  static std::unique_ptr<QuadDirective> Create(std::vector<uint64_t> bignums);

  QuadDirective(std::vector<uint64_t> bignums);

  ~QuadDirective();

  std::vector<uint64_t> bignums;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
