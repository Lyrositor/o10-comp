#include <comp/ir/data_type.h>
#include <comp/ir/variable.h>
#include <cstddef>
#include <memory>

namespace comp {
namespace ir {
Variable::Variable(std::shared_ptr<const DataType> dataType) :
  dataType(dataType) {}

std::shared_ptr<const DataType> Variable::getDataType() const {
  return this->dataType;
}

Variable::~Variable() {}
}
}
