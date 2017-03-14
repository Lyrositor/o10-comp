#pragma once

#include <vector>
#include "data_type.h"
#include "declaration.h"
#include "variable_declarator.h"

namespace comp {
namespace ast {
struct VariableDeclaration final : public Declaration {
  VariableDeclaration(
    std::shared_ptr<DataType> dataType,
    std::vector<std::shared_ptr<VariableDeclarator>> declarators,
    std::shared_ptr<SourceLocation> location = nullptr
  );
  virtual ~VariableDeclaration();

  const std::shared_ptr<DataType> dataType;
  const std::vector<std::shared_ptr<VariableDeclarator>> declarators;
};
}
}
