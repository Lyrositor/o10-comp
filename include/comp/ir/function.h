#pragma  once

#include <memory>
#include <string>
#include <vector>
#include "data_type.h"

namespace comp {
namespace ir {
class Parameter {
 public:
  Parameter(std::shared_ptr<const DataType> dataType, std::string name);
  virtual ~Parameter();
 private:
  const std::shared_ptr<const DataType> dataType;
  const std::string name;
};

class Function {
 public:
  Function(std::vector<std::shared_ptr<const Parameter>> parameters, std::shared_ptr<const DataType> returnType);
  std::shared_ptr<const DataType> getReturnType() const;
  virtual ~Function();
 private:
  std::vector<std::shared_ptr<const Parameter>> parameters;
  const std::shared_ptr<const DataType> returnType;
};
}
}
