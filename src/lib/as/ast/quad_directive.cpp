#include <comp/as/ast/quad_directive.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<QuadDirective> QuadDirective::Create(std::vector<uint64_t> bignums) {
  return std::unique_ptr<QuadDirective>(new QuadDirective(bignums));
}

QuadDirective::QuadDirective(
  std::vector<uint64_t> bignums
) :
  Directive(Type::QuadDirective),
  bignums(bignums) {
}

QuadDirective::~QuadDirective() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
