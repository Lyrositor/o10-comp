#include <comp/ir/parameter.h>

#include <cstddef>

namespace comp {
namespace ir {
std::unique_ptr<Parameter> Parameter::Create(
  std::shared_ptr<const DataType> data_type,
  std::string name
) {
  return std::unique_ptr<Parameter>(new Parameter(data_type, name));
}

Parameter::Parameter(
  std::shared_ptr<const DataType> data_type,
  std::string name
) : data_type_(data_type), name_(name) {
}

Parameter::~Parameter() {
}
}  // namespace ir
}  // namespace comp
