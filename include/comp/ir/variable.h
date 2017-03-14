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
  static std::unique_ptr<Variable> create(std::shared_ptr<const DataType> dataType);

  Variable(std::shared_ptr<const DataType> dataType);
  std::shared_ptr<const DataType> getDataType() const;
  virtual ~Variable();
 private:
  const std::shared_ptr<const DataType> dataType;
};
}
}
