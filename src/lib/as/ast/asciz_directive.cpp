#include <comp/as/ast/asciz_directive.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<AscizDirective> AscizDirective::Create(std::string value) {
  return std::unique_ptr<AscizDirective>(new AscizDirective(value));
}

AscizDirective::AscizDirective(
  std::string value
) :
  Directive(Type::AscizDirective),
  value(value) {
}

AscizDirective::~AscizDirective() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
