#pragma once

#include <memory>
#include <string>

#include "comp/ir/data_type.h"

namespace comp {
namespace ir {
class Parameter final {
 public:
  static std::unique_ptr<Parameter> Create(
    std::shared_ptr<const DataType> data_type, std::string name);

  Parameter(std::shared_ptr<const DataType> data_type, std::string name);

  ~Parameter();

  std::shared_ptr<const DataType> GetDataType() const;

  std::string GetName() const;

 private:
  const std::shared_ptr<const DataType> data_type_;
  const std::string name_;
};
}  // namespace ir
}  // namespace comp
