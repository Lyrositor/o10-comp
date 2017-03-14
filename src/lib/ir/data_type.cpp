#include <comp/ir/data_type.h>
#include <cstddef>
#include <memory>

namespace comp {
namespace ir {

DataType::DataType() {
}

DataType::~DataType() {
}

std::unique_ptr<PrimitiveDataType> PrimitiveDataType::create(size_t size) {
  return std::unique_ptr<PrimitiveDataType>(new PrimitiveDataType(size));
}

PrimitiveDataType::PrimitiveDataType(size_t size) :
  size(size) {
}

size_t PrimitiveDataType::getSize() const {
  return this->size;
}

PrimitiveDataType::~PrimitiveDataType() {
}

std::unique_ptr<ArrayDataType> ArrayDataType::create(const std::shared_ptr<const DataType> itemType, const size_t arrayLength) {
  return std::unique_ptr<ArrayDataType>(new ArrayDataType(itemType, arrayLength));
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
