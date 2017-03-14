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
  std::shared_ptr<const DataType> returnType) :
  parameters(parameters), returnType(returnType) {
}

std::shared_ptr<const DataType> Function::getReturnType() const {
  return this->returnType;
}

Function::~Function() {
}
}
}
