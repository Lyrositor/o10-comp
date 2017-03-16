#include <comp/ir/context.h>
#include <comp/ir/data_type.h>
#include <comp/ir/function.h>
#include <comp/ir/variable.h>
#include <cstddef>
#include <memory>

namespace comp {
namespace ir {
std::unique_ptr<Parameter> Parameter::Create(
  std::shared_ptr<const DataType> dataType,
  std::string name
) {
  return std::unique_ptr<Parameter>(new Parameter(dataType, name));
}

Parameter::Parameter(
  std::shared_ptr<const DataType> dataType,
  std::string name
) :
  data_type_(dataType),
  name_(name) {
}

Parameter::~Parameter() {
}

std::unique_ptr<Function> Function::Create(
  std::vector<std::shared_ptr<const Parameter>> parameters,
  std::shared_ptr<const DataType> return_type
) {
  return std::unique_ptr<Function>(new Function(parameters, return_type));
}

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
