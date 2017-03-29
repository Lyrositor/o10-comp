#include <comp/ir/data_type.h>

namespace comp {
namespace ir {

/** ----- DataType (abstract) ----- **/
DataType::DataType(const Type type): type(type) {
}

DataType::~DataType() {
}

/** ----- VoidDataType ----- **/
std::unique_ptr<VoidDataType> VoidDataType::Create() {
  return std::unique_ptr<VoidDataType>(new VoidDataType());
}

VoidDataType::VoidDataType() :
  DataType(Type::Void) {
}

VoidDataType::~VoidDataType() {
}


/** ----- IntegerDataType (abstract) ----- **/
IntegerDataType::IntegerDataType(const Type type): DataType(type) {
}

IntegerDataType::~IntegerDataType() {
}

/** ----- Uint8DataType ----- **/
std::unique_ptr<Uint8DataType> Uint8DataType::Create() {
  return std::unique_ptr<Uint8DataType>(new Uint8DataType());
}

Uint8DataType::Uint8DataType() :
    IntegerDataType(Type::Uint8) {
}

Uint8DataType::~Uint8DataType() {
}


/** ----- Int32DataType ----- **/
std::unique_ptr<Int32DataType> Int32DataType::Create() {
  return std::unique_ptr<Int32DataType>(new Int32DataType());
}

Int32DataType::Int32DataType() :
    IntegerDataType(Type::Int32) {
}

Int32DataType::~Int32DataType() {
}

/** ----- Int64DataType ----- **/
std::unique_ptr<Int64DataType> Int64DataType::Create() {
  return std::unique_ptr<Int64DataType>(new Int64DataType());
}

Int64DataType::Int64DataType() :
    IntegerDataType(Type::Int64) {
}

Int64DataType::~Int64DataType() {
}



/** ----- ArrayDataType ----- **/
std::unique_ptr<ArrayDataType> ArrayDataType::Create(
  std::shared_ptr<const DataType> itemType, size_t arrayLength) {
  return std::unique_ptr<ArrayDataType>(
    new ArrayDataType(itemType, arrayLength));
}

ArrayDataType::ArrayDataType(
  std::shared_ptr<const DataType> item_type, size_t array_length) :
  DataType(Type::Array), item_type_(item_type), size_(array_length) {
}

size_t ArrayDataType::GetSize() const {
  return this->size_;
}

ArrayDataType::~ArrayDataType() {
}

/** ----- PointerDataType ----- **/
std::unique_ptr<PointerDataType> PointerDataType::Create(
  std::shared_ptr<const DataType> pointed_type) {
  return std::unique_ptr<PointerDataType>(new PointerDataType(pointed_type));
}

PointerDataType::PointerDataType(std::shared_ptr<const DataType> pointed_type) :
  DataType(Type::Array), pointed_type_(pointed_type) {
}

PointerDataType::~PointerDataType() {
}

}  // namespace ir
}  // namespace comp
