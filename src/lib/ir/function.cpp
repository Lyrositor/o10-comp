#include <comp/ir/context.h>
#include <comp/ir/data_type.h>
#include <comp/ir/function.h>
#include <comp/ir/variable.h>
#include <cstddef>
#include <memory>

namespace comp {
namespace ir {
Function::Function(
  std::vector<std::shared_ptr<const Parameter>> parameters,
  std::shared_ptr<const DataType> return_type) :
  parameters_(parameters), return_type_(return_type) {
}

std::shared_ptr<const DataType> Function::GetReturnType() const {
  return this->return_type_;
}

Function::~Function() {
}
}
}
