#include <comp/as/ast/cfi_startproc_directive.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<CfiStartprocDirective> CfiStartprocDirective::Create() {
  return std::unique_ptr<CfiStartprocDirective>(new CfiStartprocDirective());
}

CfiStartprocDirective::CfiStartprocDirective() :
  Directive(Type::CfiStartprocDirective) {
}

CfiStartprocDirective::~CfiStartprocDirective() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
