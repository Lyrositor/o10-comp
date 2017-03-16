#include <comp/ir/data_type.h>
#include <cstddef>
#include <memory>

namespace comp {
namespace ir {

DataType::DataType() {
}

DataType::~DataType() {
}

std::unique_ptr<PrimitiveDataType> PrimitiveDataType::Create(size_t size) {
  return std::unique_ptr<PrimitiveDataType>(new PrimitiveDataType(size));
}

PrimitiveDataType::PrimitiveDataType(size_t size) :
  size_(size) {
}

size_t PrimitiveDataType::GetSize() const {
  return this->size_;
}

PrimitiveDataType::~PrimitiveDataType() {
}

std::unique_ptr<ArrayDataType> ArrayDataType::Create(std::shared_ptr<const DataType> itemType,
                                                     size_t arrayLength) {
  return std::unique_ptr<ArrayDataType>(new ArrayDataType(itemType, arrayLength));
}

ArrayDataType::ArrayDataType(std::shared_ptr<const DataType> item_type, size_t array_length) :
  item_type_(item_type), length_(array_length) {
}

size_t ArrayDataType::GetSize() const {
  return this->length_ * this->item_type_->GetSize();
}

ArrayDataType::~ArrayDataType() {
}

std::shared_ptr<const PrimitiveDataType> kVoidType(new PrimitiveDataType(0));
std::shared_ptr<const PrimitiveDataType> kCharType(new PrimitiveDataType(1));
std::shared_ptr<const PrimitiveDataType> kInt32Type(new PrimitiveDataType(4));
std::shared_ptr<const PrimitiveDataType> kInt64Type(new PrimitiveDataType(8));
}
}
