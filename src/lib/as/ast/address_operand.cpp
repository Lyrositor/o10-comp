#include <comp/as/ast/address_operand.h>

namespace comp {
namespace as {
namespace ast {
std::unique_ptr<AddressOperand> AddressOperand::Create(
  std::shared_ptr<AddressExpression> address
) {
  return std::unique_ptr<AddressOperand>(new AddressOperand(address));
}

AddressOperand::AddressOperand(std::shared_ptr<AddressExpression> address
) : SimpleOperand(ast::Node::Type::AddressOperand), address(address) {
}

AddressOperand::~AddressOperand() {
}
}  // namespace ast
}  // namespace as
}  // namespace comp
