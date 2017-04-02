#include <comp/dot/ast/assignment.h>

namespace comp {
namespace dot {
namespace ast {
std::unique_ptr<Assignment> Assignment::Create(
  std::string key,
  std::string value
) {
  return std::unique_ptr<Assignment>(new Assignment(key, value));
}

Assignment::Assignment(
  std::string key,
  std::string value
) :
  Node(Type::Assignment),
  key(key),
  value(value) {
}

Assignment::~Assignment() {
}
}  // namespace ast
}  // namespace dot
}  // namespace comp
