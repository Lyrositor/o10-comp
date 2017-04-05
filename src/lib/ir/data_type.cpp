#include <comp/ir/data_type.h>

namespace comp {
namespace ir {

/** ----- DataType (abstract) ----- **/
DataType::DataType(const Type type) : type_(type) {
}

DataType::~DataType() {
}

DataType::Type DataType::GetType() const {
  return type_;
}

bool DataType::IsCastableTo(const DataType &other) const {
  return other.IsCastableFrom(*this);
}

bool DataType::operator!=(const DataType &other) const {
  return !(*this == other);
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

bool VoidDataType::IsCastableFrom(const DataType &other) const {
  return other.GetType() == Type::Void;
}

std::unique_ptr<DataType> VoidDataType::GetCommonType(const DataType &other) const {
  if (other.GetType() != Type::Void) {
    throw std::runtime_error("Incompatible type with `void`");
  }
  return VoidDataType::Create();
}

bool VoidDataType::operator==(const DataType &other) const {
  return other.GetType() == Type::Void;
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

bool Uint8DataType::IsCastableFrom(const DataType &other) const {
  switch (other.GetType()) {
    case Type::Uint8:
    case Type::Int32:
    case Type::Int64: {
      return true;
    }
    default: {
      return false;
    }
  }
}

std::unique_ptr<DataType> Uint8DataType::GetCommonType(const DataType &other) const {
  switch (other.GetType()) {
    case Type::Uint8: {
      return Uint8DataType::Create();
    }
    case Type::Int32: {
      return Int32DataType::Create();
    }
    case Type::Int64: {
      return Int64DataType::Create();
    }
    default: {
      throw std::runtime_error("Incompatible type with `uint8_t`");
    }
  }
}

bool Uint8DataType::operator==(const DataType &other) const {
  return other.GetType() == Type::Uint8;
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

bool Int32DataType::IsCastableFrom(const DataType &other) const {
  switch (other.GetType()) {
    case Type::Uint8:
    case Type::Int32:
    case Type::Int64: {
      return true;
    }
    default: {
      return false;
    }
  }
}

std::unique_ptr<DataType> Int32DataType::GetCommonType(const DataType &other) const {
  switch (other.GetType()) {
    case Type::Uint8:
    case Type::Int32: {
      return Int32DataType::Create();
    }
    case Type::Int64: {
      return Int64DataType::Create();
    }
    default: {
      throw std::runtime_error("Incompatible type with `int32_t`");
    }
  }
}

bool Int32DataType::operator==(const DataType &other) const {
  return other.GetType() == Type::Int32;
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

bool Int64DataType::IsCastableFrom(const DataType &other) const {
  switch (other.GetType()) {
    case Type::Uint8:
    case Type::Int32:
    case Type::Int64: {
      return true;
    }
    default: {
      return false;
    }
  }
}

std::unique_ptr<DataType> Int64DataType::GetCommonType(const DataType &other) const {
  switch (other.GetType()) {
    case Type::Uint8:
    case Type::Int32:
    case Type::Int64: {
      return Int64DataType::Create();
    }
    default: {
      throw std::runtime_error("Incompatible type with `int64_t`");
    }
  }
}

bool Int64DataType::operator==(const DataType &other) const {
  return other.GetType() == Type::Int64;
}

/** ----- ArrayDataType ----- **/
std::unique_ptr<ArrayDataType> ArrayDataType::Create(
  std::shared_ptr<const DataType> item_type, size_t arrayLength) {
  return std::unique_ptr<ArrayDataType>(
    new ArrayDataType(item_type, arrayLength));
}

ArrayDataType::ArrayDataType(
  std::shared_ptr<const DataType> item_type, size_t array_length) :
  DataType(Type::Array), item_type_(item_type), size_(array_length) {
}

std::shared_ptr<const DataType> ArrayDataType::GetItemType() const {
  return item_type_;
}

size_t ArrayDataType::GetSize() const {
  return this->size_;
}

ArrayDataType::~ArrayDataType() {
}

bool ArrayDataType::IsCastableFrom(const DataType &other) const {
  return *this == other;
}

std::unique_ptr<DataType> ArrayDataType::GetCommonType(const DataType &other) const {
  if (*this == other) {
    return ArrayDataType::Create(this->item_type_, this->size_);
  }
  throw std::runtime_error("Incompatible type with `array`");
}

bool ArrayDataType::operator==(const DataType &other) const {
  if(other.GetType() != Type::Array) {
    return false;
  }
  const ArrayDataType other_array = static_cast<const ArrayDataType &>(other);
  return this->size_ == other_array.size_ && *this->item_type_ == *other_array.item_type_;
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

bool PointerDataType::IsCastableFrom(const DataType &other) const {
  return *this == other;
}

std::unique_ptr<DataType> PointerDataType::GetCommonType(const DataType &other) const {
  if (*this == other) {
    return PointerDataType::Create(this->pointed_type_);
  }
  throw std::runtime_error("Incompatible type with `pointer`");
}

bool PointerDataType::operator==(const DataType &other) const {
  if(other.GetType() != Type::Pointer) {
    return false;
  }
  const PointerDataType other_pointer = static_cast<const PointerDataType &>(other);
  return *this->pointed_type_ == *other_pointer.pointed_type_;
}
}  // namespace ir
}  // namespace comp
