#pragma once

#include <memory>
#include <cstddef>

namespace comp {
namespace ir {
class DataType {
 public:
  DataType();
  virtual ~DataType() = 0;
  virtual size_t GetSize() const = 0;
};

class PrimitiveDataType final : public DataType {
 public:
  static std::unique_ptr<PrimitiveDataType> Create(size_t size);

  PrimitiveDataType(size_t size);
  virtual ~PrimitiveDataType();
  size_t GetSize() const;
 private:
  const size_t size_;
};

class ArrayDataType final : public DataType {
 public:
  static std::unique_ptr<ArrayDataType> Create(
    std::shared_ptr<const DataType> itemType,
    size_t arrayLength
  );

  ArrayDataType(std::shared_ptr<const DataType> item_type, size_t array_length);
  virtual ~ArrayDataType();
  size_t GetSize() const;
 private:
  const std::shared_ptr<const DataType> item_type_;
  const size_t length_;
};

// Built-in types
extern std::shared_ptr<const PrimitiveDataType> kVoidType;
extern std::shared_ptr<const PrimitiveDataType> kCharType;
extern std::shared_ptr<const PrimitiveDataType> kInt32Type;
extern std::shared_ptr<const PrimitiveDataType> kInt64Type;
}
}
