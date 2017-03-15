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
  static std::unique_ptr<Variable> Create(std::shared_ptr<const DataType> dataType);

  Variable(std::shared_ptr<const DataType> data_type);
  virtual ~Variable();
  std::shared_ptr<const DataType> GetDataType() const;
 private:
  const std::shared_ptr<const DataType> data_type_;
};
}
}
