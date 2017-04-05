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

  DataType(const Type type);
  virtual ~DataType() = 0;

  Type GetType() const;

  /**
   * Returns true if a value of type `this` can be casted from a value of type `other`.
   */
  virtual bool IsCastableFrom(const DataType &other) const = 0;
  bool IsCastableTo(const DataType &other) const;
  virtual std::unique_ptr<DataType> GetCommonType(const DataType &other) const = 0;
  virtual bool operator==(const DataType &other) const = 0;
  bool operator!=(const DataType &other) const;

 private:
  const Type type_;
};

class VoidDataType final : public DataType {
 public:
  static std::unique_ptr<VoidDataType> Create();

  VoidDataType();
  ~VoidDataType();

  bool IsCastableFrom(const DataType &other) const;
  std::unique_ptr<DataType> GetCommonType(const DataType &other) const;
  bool operator==(const DataType &other) const;
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

  bool IsCastableFrom(const DataType &other) const;
  std::unique_ptr<DataType> GetCommonType(const DataType &other) const;
  bool operator==(const DataType &other) const;
};

class Int32DataType final : public IntegerDataType {
 public:
  static std::unique_ptr<Int32DataType> Create();

  Int32DataType();
  virtual ~Int32DataType();

  bool IsCastableFrom(const DataType &other) const;
  std::unique_ptr<DataType> GetCommonType(const DataType &other) const;
  bool operator==(const DataType &other) const;
};

class Int64DataType final : public IntegerDataType {
 public:
  static std::unique_ptr<Int64DataType> Create();

  Int64DataType();
  virtual ~Int64DataType();

  bool IsCastableFrom(const DataType &other) const;
  std::unique_ptr<DataType> GetCommonType(const DataType &other) const;
  bool operator==(const DataType &other) const;
};


class ArrayDataType final : public DataType {
 public:
  static std::unique_ptr<ArrayDataType> Create(
    std::shared_ptr<const DataType> item_type,
    size_t arrayLength);

  ArrayDataType(std::shared_ptr<const DataType> item_type, size_t array_length);
  virtual ~ArrayDataType();
  std::shared_ptr<const DataType> GetItemType() const;
  size_t GetSize() const; // Returns the number of cells in the array

  bool IsCastableFrom(const DataType &other) const;
  std::unique_ptr<DataType> GetCommonType(const DataType &other) const;
  bool operator==(const DataType& other) const;
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

  std::shared_ptr<const DataType> GetItemType() const;
  bool IsCastableFrom(const DataType &other) const;
  std::unique_ptr<DataType> GetCommonType(const DataType &other) const;
  bool operator==(const DataType& other) const;
 private:
  const std::shared_ptr<const DataType> pointed_type_;
};
}  // namespace ir
}  // namespace comp
