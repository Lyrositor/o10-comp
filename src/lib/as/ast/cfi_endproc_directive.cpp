#include <comp/as/ast/cfi_endproc_directive.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<CfiEndprocDirective> CfiEndprocDirective::Create() {
  return std::unique_ptr<CfiEndprocDirective>(new CfiEndprocDirective());
}

CfiEndprocDirective::CfiEndprocDirective() :
  Directive(Type::CfiEndprocDirective) {
}

CfiEndprocDirective::~CfiEndprocDirective() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
