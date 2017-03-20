#include <comp/as/ast/immediate_operand.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<ImmediateOperand> ImmediateOperand::Create(int64_t value) {
  return std::unique_ptr<ImmediateOperand>(new ImmediateOperand(value));
}

ImmediateOperand::ImmediateOperand(
  int64_t value
) :
  SimpleOperand(Type::ImmediateOperand),
  value(value) {
}

ImmediateOperand::~ImmediateOperand() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
