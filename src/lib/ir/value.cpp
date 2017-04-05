#include <comp/ir/value.h>

namespace comp {
namespace ir {

/** ----- Value (abstract) ----- **/
Value::Value(
  std::shared_ptr<const DataType> data_type
) : data_type_(data_type) {
}

Value::~Value() {
}

std::shared_ptr<const DataType> Value::GetDataType() const {
  return this->data_type_;
}

DataType::Type Value::GetType() const {
  return this->data_type_->GetType();
}

/** ----- Uint8Value ----- **/
std::unique_ptr<Uint8Value> Uint8Value::Create(
  uint8_t value,
  std::shared_ptr<const Uint8DataType> data_type) {
  return std::unique_ptr<Uint8Value>(new Uint8Value(value, data_type));
}

Uint8Value::Uint8Value(
  uint8_t value,
  std::shared_ptr<const Uint8DataType> data_type
) :
  Value(data_type),
  value_(value) {
}

Uint8Value::~Uint8Value() {
}

uint8_t Uint8Value::Get() const {
  return this->value_;
}

/** ----- Int32DataType ----- **/
std::unique_ptr<Int32Value> Int32Value::Create(
  int32_t value,
  std::shared_ptr<const Int32DataType> data_type) {
  return std::unique_ptr<Int32Value>(new Int32Value(value, data_type));
}

Int32Value::Int32Value(
  int32_t value,
  std::shared_ptr<const Int32DataType> data_type
) :
  Value(data_type),
  value_(value) {
}

Int32Value::~Int32Value() {
}

int32_t Int32Value::Get() const {
  return this->value_;
}

/** ----- Int64Value ----- **/
std::unique_ptr<Int64Value> Int64Value::Create(
  int64_t value,
  std::shared_ptr<const Int64DataType> data_type) {
  return std::unique_ptr<Int64Value>(new Int64Value(value, data_type));
}

Int64Value::Int64Value(
  int64_t value,
  std::shared_ptr<const Int64DataType> data_type
) :
  Value(data_type),
  value_(value) {
}

Int64Value::~Int64Value() {
}

int64_t Int64Value::Get() const {
  return this->value_;
}
}  // namespace ir
}  // namespace comp
