#include <comp/as/ast/text_directive.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<TextDirective> TextDirective::Create(size_t subsection) {
  return std::unique_ptr<TextDirective>(new TextDirective(subsection));
}

TextDirective::TextDirective(
  size_t subsection
) :
  Directive(Type::TextDirective),
  subsection(subsection) {
}

TextDirective::~TextDirective() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
