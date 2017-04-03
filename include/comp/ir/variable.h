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
    std::shared_ptr<const ast::Node> ast_node = nullptr);

  Variable(
    std::shared_ptr<const DataType> data_type,
    std::shared_ptr<const ast::Node> ast_node = nullptr);

  virtual ~Variable();

  std::shared_ptr<const DataType> GetDataType() const;

  /** Returns the AST node that created this variable. Can be the `nullptr`. */
  std::shared_ptr<const ast::Node> GetAstNode() const;

 private:
  const std::shared_ptr<const DataType> data_type_;
  const std::shared_ptr<const ast::Node> ast_node_;
};
}  // namespace ir
}  // namespace comp
