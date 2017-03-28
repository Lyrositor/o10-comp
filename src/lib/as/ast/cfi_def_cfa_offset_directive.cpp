#include <comp/as/ast/cfi_def_cfa_offset_directive.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<CfiDefCfaOffsetDirective> CfiDefCfaOffsetDirective::Create(
  std::shared_ptr<Expression> size
) {
  return std::unique_ptr<CfiDefCfaOffsetDirective>(new CfiDefCfaOffsetDirective(size));
}

CfiDefCfaOffsetDirective::CfiDefCfaOffsetDirective(
  std::shared_ptr<Expression> size
) :
  Directive(Type::CfiDefCfaOffsetDirective),
  size(size) {
}

CfiDefCfaOffsetDirective::~CfiDefCfaOffsetDirective() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
