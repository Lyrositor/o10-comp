#include <comp/ir/variable.h>

#include <cstddef>

namespace comp {
namespace ir {
std::unique_ptr<Variable> Variable::Create(
  std::shared_ptr<const DataType> data_type,
  std::shared_ptr<const ast::Node> ast_node
) {
  return std::unique_ptr<Variable>(new Variable(data_type, ast_node));
}

Variable::Variable(
  std::shared_ptr<const DataType> data_type,
  std::shared_ptr<const ast::Node> ast_node
) : data_type_(data_type), ast_node_(ast_node) {
}

std::shared_ptr<const DataType> Variable::GetDataType() const {
  return this->data_type_;
}

std::shared_ptr<const ast::Node> Variable::GetAstNode() const {
  return this->ast_node_;
}

Variable::~Variable() {
}
}  // namespace ir
}  // namespace comp
