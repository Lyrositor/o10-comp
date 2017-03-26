#include <comp/ir/variable.h>

#include <cstddef>

namespace comp {
namespace ir {
std::unique_ptr<Variable> Variable::Create(
  std::shared_ptr<const DataType> data_type,
  std::shared_ptr<const ast::Declarator> declarator
) {
  return std::unique_ptr<Variable>(new Variable(data_type, declarator));
}

Variable::Variable(
  std::shared_ptr<const DataType> data_type,
  std::shared_ptr<const ast::Declarator> declarator
) : data_type_(data_type), declarator_(declarator) {
}

std::shared_ptr<const DataType> Variable::GetDataType() const {
  return this->data_type_;
}

std::shared_ptr<const ast::Declarator> Variable::GetDeclarator() const {
  return this->declarator_;
}


Variable::~Variable() {
}
}  // namespace ir
}  // namespace comp
