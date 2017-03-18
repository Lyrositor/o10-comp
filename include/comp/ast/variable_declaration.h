#pragma once

#include <vector>

#include "comp/ast/data_type.h"
#include "comp/ast/declaration.h"
#include "comp/ast/variable_declarator.h"

namespace comp {
namespace ast {
struct VariableDeclaration final : public Declaration {
  static std::unique_ptr<VariableDeclaration> Create(
    std::shared_ptr<DataType> data_type,
    std::vector<std::shared_ptr<VariableDeclarator>> declarators,
    std::shared_ptr<SourceLocation> location = nullptr);

  VariableDeclaration(
    std::shared_ptr<DataType> data_type,
    std::vector<std::shared_ptr<VariableDeclarator>> declarators,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~VariableDeclaration();

  const std::shared_ptr<DataType> data_type;
  const std::vector<std::shared_ptr<VariableDeclarator>> declarators;
};
}  // namespace ast
}  // namespace comp
