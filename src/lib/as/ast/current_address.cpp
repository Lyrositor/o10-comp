#include <comp/as/ast/current_address.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<CurrentAddress> CurrentAddress::Create() {
  return std::unique_ptr<CurrentAddress>(new CurrentAddress());
}

CurrentAddress::CurrentAddress() :
  Expression(Type::CurrentAddress) {
}

CurrentAddress::~CurrentAddress() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
