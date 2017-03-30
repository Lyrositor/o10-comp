#include <comp/as/ast/cfi_def_cfa_offset_directive.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<CfiDefCfaOffsetDirective> CfiDefCfaOffsetDirective::Create(
  std::shared_ptr<Expression> offset
) {
  return std::unique_ptr<CfiDefCfaOffsetDirective>(new CfiDefCfaOffsetDirective(offset));
}

CfiDefCfaOffsetDirective::CfiDefCfaOffsetDirective(
  std::shared_ptr<Expression> offset
) :
  Directive(Type::CfiDefCfaOffsetDirective),
  offset(offset) {
}

CfiDefCfaOffsetDirective::~CfiDefCfaOffsetDirective() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
