#pragma once

#include <vector>
#include "data_type.h"
#include "declaration.h"
#include "variable_declarator.h"

namespace comp {
namespace ast {
struct VariableDeclaration final : public Declaration {
  static std::unique_ptr<VariableDeclaration> Create(
    std::shared_ptr<DataType> dataType,
    std::vector<std::shared_ptr<VariableDeclarator>> declarators,
    std::shared_ptr<SourceLocation> location = nullptr
  );

  VariableDeclaration(
    std::shared_ptr<DataType> dataType,
    std::vector<std::shared_ptr<VariableDeclarator>> declarators,
    std::shared_ptr<SourceLocation> location = nullptr
  );

  ~VariableDeclaration();

  const std::shared_ptr<DataType> dataType;
  const std::vector<std::shared_ptr<VariableDeclarator>> declarators;
};
}
}
