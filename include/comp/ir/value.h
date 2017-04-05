#pragma once

#include <cstddef>
#include <memory>
#include "comp/ir/builtins.h"
#include "comp/ir/data_type.h"

namespace comp {
namespace ir {
/**
 * Represents a known value
 */
class Value {
 public:
  Value(std::shared_ptr<const DataType> data_type);
  virtual ~Value() = 0;

  std::shared_ptr<const DataType> GetDataType() const;
  DataType::Type GetType() const;

 protected:
  const std::shared_ptr<const DataType> data_type_;
};

class Uint8Value final : protected Value {
 public:
  static std::unique_ptr<Uint8Value> Create(uint8_t value, std::shared_ptr<const Uint8DataType> = GetUint8Type());

  Uint8Value(uint8_t value, std::shared_ptr<const Uint8DataType> = GetUint8Type());
  ~Uint8Value();

  uint8_t Get() const;

 protected:
  const std::shared_ptr<const Uint8DataType> data_type_;
  const uint8_t value_;
};

class Int32Value final : protected Value {
 public:
  static std::unique_ptr<Int32Value> Create(int32_t value, std::shared_ptr<const Int32DataType> = GetInt32Type());

  Int32Value(int32_t value, std::shared_ptr<const Int32DataType> = GetInt32Type());
  ~Int32Value();

  int32_t Get() const;

 protected:
  const std::shared_ptr<const Int32DataType> data_type_;
  const int32_t value_;
};

class Int64Value final : protected Value {
 public:
  static std::unique_ptr<Int64Value> Create(int64_t value, std::shared_ptr<const Int64DataType> = GetInt64Type());

  Int64Value(int64_t value, std::shared_ptr<const Int64DataType> = GetInt64Type());
  ~Int64Value();

  int64_t Get() const;

 protected:
  const std::shared_ptr<const Int64DataType> data_type_;
  const int64_t value_;
};
}  // namespace ir
}  // namespace comp
