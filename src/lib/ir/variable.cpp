#include <comp/ir/variable.h>

#include <cstddef>

namespace comp {
namespace ir {
Variable::Variable(std::shared_ptr<const DataType> data_type) :
  data_type_(data_type) {
}

std::shared_ptr<const DataType> Variable::GetDataType() const {
  return this->data_type_;
}

Variable::~Variable() {
}

std::unique_ptr<Variable> Variable::Create(
  std::shared_ptr<const DataType> data_type) {
  return std::unique_ptr<Variable>(new Variable(data_type));
}
}  // namespace ir
}  // namespace comp
