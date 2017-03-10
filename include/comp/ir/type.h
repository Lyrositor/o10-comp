#pragma  once

#include <memory>
#include <cstddef>

namespace comp {
namespace ir {
class Type {
 public:
  Type();
  virtual size_t getSize() const = 0;
  virtual ~Type() = 0;
};

class PrimitiveType final : public Type {
 public:
  PrimitiveType(size_t size);
  size_t getSize() const;
  virtual ~PrimitiveType();
 private:
  size_t size;
};

class ArrayType final : public Type {
 public:
  ArrayType(std::shared_ptr<const Type> itemType, size_t arrayLength);
  size_t getSize() const;
  virtual ~ArrayType();
 private:
  std::shared_ptr<const Type> itemType;
  size_t length;
};

// Built-in types
const PrimitiveType voidType(0);
const PrimitiveType int32Type(4);
const PrimitiveType int64Type(8);
const PrimitiveType charType(1);
//const std::shared_ptr<const PrimitiveType> voidTypePointer(&voidType);
//const std::shared_ptr<const PrimitiveType> int32TypePointer(&int32Type);
//const std::shared_ptr<const PrimitiveType> int64TypePointer(&int64Type);
//const std::shared_ptr<const PrimitiveType> charTypePointer(&charType);
}
}
