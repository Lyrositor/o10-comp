#pragma  once

#include <memory>
#include <cstddef>

namespace comp {
namespace ir {
class DataType {
 public:
  DataType();
  virtual size_t getSize() const = 0;
  virtual ~DataType() = 0;
};

class PrimitiveDataType final : public DataType {
 public:
  PrimitiveDataType(size_t size);
  size_t getSize() const;
  virtual ~PrimitiveDataType();
 private:
  const size_t size;
};

class ArrayDataType final : public DataType {
 public:
  ArrayDataType(std::shared_ptr<const DataType> itemType, size_t arrayLength);
  size_t getSize() const;
  virtual ~ArrayDataType();
 private:
  const std::shared_ptr<const DataType> itemType;
  const size_t length;
};

// Built-in types
const std::shared_ptr<const PrimitiveDataType> voidType(new PrimitiveDataType(0));
const std::shared_ptr<const PrimitiveDataType> charType(new PrimitiveDataType(1));
const std::shared_ptr<const PrimitiveDataType> int32Type(new PrimitiveDataType(4));
const std::shared_ptr<const PrimitiveDataType> int64Type(new PrimitiveDataType(8));
}
}
