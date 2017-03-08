#pragma once

#include <vector>
#include "ctype.h"
#include "declaration.h"
#include "variable_declarator.h"

namespace comp {
namespace ast {
struct VariableDeclaration final : public Declaration {
  VariableDeclaration(
    Type type,
    std::vector<std::shared_ptr<VariableDeclarator>> declarators,
    std::shared_ptr<SourceLocation> location = nullptr
  );
  virtual ~VariableDeclaration();

  const Type type;
  const std::vector<std::shared_ptr<VariableDeclarator>> declarators;
};
}
}
