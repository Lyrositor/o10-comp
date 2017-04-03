#include <comp/as/ast/align_directive.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<AlignDirective> AlignDirective::Create(
  std::shared_ptr<AddressExpression> alignment_value,
  std::shared_ptr<AddressExpression> fill_value,
  std::shared_ptr<AddressExpression> max_skipped_bytes) {
  return std::unique_ptr<AlignDirective>(new AlignDirective(alignment_value, fill_value, max_skipped_bytes));
}

AlignDirective::AlignDirective(
  std::shared_ptr<AddressExpression> alignment_value,
  std::shared_ptr<AddressExpression> fill_value,
  std::shared_ptr<AddressExpression> max_skipped_bytes
) :
  Directive(Type::AlignDirective),
  alignment_value(alignment_value),
  fill_value(fill_value),
  max_skipped_bytes(max_skipped_bytes) {
}

AlignDirective::~AlignDirective() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
