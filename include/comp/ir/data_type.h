#pragma once

#include <cstddef>
#include <memory>

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
    size_t arrayLength);

  ArrayDataType(std::shared_ptr<const DataType> item_type, size_t array_length);
  virtual ~ArrayDataType();
  size_t GetSize() const;
 private:
  const std::shared_ptr<const DataType> item_type_;
  const size_t length_;
};

class PointerDataType final : public DataType {
 public:
  static std::unique_ptr<PointerDataType> Create(
    std::shared_ptr<const DataType> pointed_type);

  PointerDataType(std::shared_ptr<const DataType> pointed_type);

  ~PointerDataType();

  size_t GetSize() const;
 private:
  const std::shared_ptr<const DataType> pointed_type_;
};
}  // namespace ir
}  // namespace comp
