#pragma  once

#include <memory>
#include <string>
#include <vector>
#include "data_type.h"

namespace comp {
namespace ir {
class Parameter final {
 public:
  static std::unique_ptr<Parameter> Create(std::shared_ptr<const DataType> dataType, std::string name);
  Parameter(std::shared_ptr<const DataType> dataType, std::string name);
  ~Parameter();
 private:
  const std::shared_ptr<const DataType> data_type_;
  const std::string name_;
};

/**
 * This represents a C function.
 * TODO: Add a pointer to the AST node for the declaration and definition.
 * If the declaration node is `nullptr`, the function is a builtin.
 */
class Function final {
 public:
  static std::unique_ptr<Function> Create(
    std::vector<std::shared_ptr<const Parameter>> parameters,
    std::shared_ptr<const DataType> return_type
  );
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
