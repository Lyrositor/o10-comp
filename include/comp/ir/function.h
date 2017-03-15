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
  const std::shared_ptr<const DataType> data_type_;
  const std::string name_;
};

class Function {
 public:
  Function(
    std::vector<std::shared_ptr<const Parameter>> parameters,
    std::shared_ptr<const DataType> return_type
  );
  virtual ~Function();
  std::shared_ptr<const DataType> GetReturnType() const;
 private:
  std::vector<std::shared_ptr<const Parameter>> parameters_;
  const std::shared_ptr<const DataType> return_type_;
};
}
}
