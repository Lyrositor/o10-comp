#pragma once

#include <memory>
#include "comp/as/ast/directive.h"
#include "comp/as/ast/address_expression.h"

namespace comp {
namespace as {
namespace ast {
/**
 * @see: https://sourceware.org/binutils/docs/as/Align.html#Align
 */
struct AlignDirective final : public Directive {
  static std::unique_ptr<AlignDirective> Create(
      std::shared_ptr<AddressExpression> alignment_value,
      std::shared_ptr<AddressExpression> fill_value = nullptr,
      std::shared_ptr<AddressExpression> max_skipped_bytes = nullptr);

  AlignDirective(
      std::shared_ptr<AddressExpression> alignment_value,
      std::shared_ptr<AddressExpression> fill_value = nullptr,
      std::shared_ptr<AddressExpression> max_skipped_bytes = nullptr);

  ~AlignDirective();

  std::shared_ptr<AddressExpression> alignment_value;
  std::shared_ptr<AddressExpression> fill_value;
  std::shared_ptr<AddressExpression> max_skipped_bytes;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
