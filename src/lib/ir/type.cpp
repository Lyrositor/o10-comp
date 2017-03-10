#include <comp/ir/type.h>
#include <cstddef>
#include <memory>

namespace comp {
namespace ir {

Type::Type() {
}

Type::~Type() {
}

PrimitiveType::PrimitiveType(size_t size) :
  size(size) {
}

size_t PrimitiveType::getSize() const {
  return this->size;
}

PrimitiveType::~PrimitiveType() {
}

ArrayType::ArrayType(std::shared_ptr<const Type> itemType, size_t arrayLength) :
  itemType(itemType), length(arrayLength) {
}

size_t ArrayType::getSize() const {
  return this->length * this->itemType->getSize();
}

ArrayType::~ArrayType() {
}
}
}
