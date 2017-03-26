#pragma once

#include <memory>

#include "comp/ast/declarator.h"
#include "comp/ir/data_type.h"

namespace comp {
namespace ir {

/**
 * Represents a place in memory.
 * It also encompasses constants.
 */
class Variable {
 public:
  static std::unique_ptr<Variable> Create(
    std::shared_ptr<const DataType> data_type,
    std::shared_ptr<const ast::Declarator> declarator);

  Variable(
    std::shared_ptr<const DataType> data_type,
    std::shared_ptr<const ast::Declarator> declarator);

  virtual ~Variable();

  std::shared_ptr<const DataType> GetDataType() const;

  std::shared_ptr<const ast::Declarator> GetDeclarator() const;

 private:
  const std::shared_ptr<const DataType> data_type_;
  const std::shared_ptr<const ast::Declarator> declarator_;
};
}  // namespace ir
}  // namespace comp
