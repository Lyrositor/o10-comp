#include <comp/as/ast/cfi_offset_directive.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<CfiOffsetDirective> CfiOffsetDirective::Create(
  std::shared_ptr<RegisterOperand> reg,
  std::shared_ptr<AddressExpression> size
) {
  return std::unique_ptr<CfiOffsetDirective>(new CfiOffsetDirective(reg, size));
}

CfiOffsetDirective::CfiOffsetDirective(
  std::shared_ptr<RegisterOperand> reg,
  std::shared_ptr<AddressExpression> size
) :
  Directive(Type::CfiOffsetDirective),
  reg(reg),
  size(size) {
}

CfiOffsetDirective::~CfiOffsetDirective() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
