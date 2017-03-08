#pragma once

#include <vector>
#include "ctype.h"
#include "declaration.h"
#include "variable_declarator.h"

namespace comp {
namespace ast {
struct VariableDeclaration : public Declaration {
  VariableDeclaration(
    CType type,
    std::vector<std::shared_ptr<VariableDeclarator>> declarators
  );
  virtual ~VariableDeclaration();

  const CType type;
  const std::vector<std::shared_ptr<VariableDeclarator>> declarators;
};
}
}
