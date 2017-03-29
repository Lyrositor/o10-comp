#pragma once

#include <cstddef>
#include <memory>

namespace comp {
namespace ir {
class DataType {
 public:
  enum class Type {
    Void,
    Uint8,
    Int32,
    Int64,
    Pointer,
    Array
  };

 public:
  DataType(const Type type);
  virtual ~DataType() = 0;

 private:
  const Type type;
};

class VoidDataType final : public DataType {
 public:
  static std::unique_ptr<VoidDataType> Create();

  VoidDataType();
  virtual ~VoidDataType();
};

class IntegerDataType : public DataType {
 public:
  IntegerDataType(const Type type);
  virtual ~IntegerDataType() = 0;
};

class Uint8DataType final : public IntegerDataType {
 public:
  static std::unique_ptr<Uint8DataType> Create();

  Uint8DataType();
  virtual ~Uint8DataType();
};

class Int32DataType final : public IntegerDataType {
 public:
  static std::unique_ptr<Int32DataType> Create();

  Int32DataType();
  virtual ~Int32DataType();
};

class Int64DataType final : public IntegerDataType {
 public:
  static std::unique_ptr<Int64DataType> Create();

  Int64DataType();
  virtual ~Int64DataType();
};


class ArrayDataType final : public DataType {
 public:
  static std::unique_ptr<ArrayDataType> Create(
    std::shared_ptr<const DataType> itemType,
    size_t arrayLength);

  ArrayDataType(std::shared_ptr<const DataType> item_type, size_t array_length);
  virtual ~ArrayDataType();
  size_t GetSize() const; // Returns the number of cells in the array
 private:
  const std::shared_ptr<const DataType> item_type_;
  const size_t size_; // Number of cells in the array
};

class PointerDataType final : public DataType {
 public:
  static std::unique_ptr<PointerDataType> Create(
    std::shared_ptr<const DataType> pointed_type);

  PointerDataType(std::shared_ptr<const DataType> pointed_type);

  ~PointerDataType();

 private:
  const std::shared_ptr<const DataType> pointed_type_;
};
}  // namespace ir
}  // namespace comp
