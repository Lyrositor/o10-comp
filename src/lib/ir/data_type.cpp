#include <comp/ir/data_type.h>
#include <cstddef>
#include <memory>

namespace comp {
namespace ir {

DataType::DataType() {
}

DataType::~DataType() {
}

PrimitiveDataType::PrimitiveDataType(size_t size) :
  size(size) {
}

size_t PrimitiveDataType::getSize() const {
  return this->size;
}

PrimitiveDataType::~PrimitiveDataType() {
}

ArrayDataType::ArrayDataType(std::shared_ptr<const DataType> itemType, size_t arrayLength) :
  itemType(itemType), length(arrayLength) {
}

size_t ArrayDataType::getSize() const {
  return this->length * this->itemType->getSize();
}

ArrayDataType::~ArrayDataType() {
}
}
}
