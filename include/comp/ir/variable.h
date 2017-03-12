#pragma  once

#include <memory>
#include "data_type.h"

namespace comp {
namespace ir {

/**
 * Represents a place in memory.
 * It also encompasses constants.
 */
class Variable {
 public:
  Variable(std::shared_ptr<const DataType> dataType);
  std::shared_ptr<const DataType> getDataType() const;
  virtual ~Variable();
 private:
  const std::shared_ptr<const DataType> dataType;
};
}
}
