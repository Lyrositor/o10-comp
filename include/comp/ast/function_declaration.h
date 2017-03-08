#pragma once

#include <memory>
#include <vector>
#include "block_statement.h"
#include "declaration.h"
#include "parameter.h"
#include "identifier.h"

namespace comp {
namespace ast {
struct FunctionDeclaration : public Declaration {
  FunctionDeclaration(
    std::shared_ptr<Identifier> identifier,
    std::vector<std::shared_ptr<Parameter>> parameters,
    std::shared_ptr<BlockStatement> body
  );
  virtual ~FunctionDeclaration();

  const std::shared_ptr<Identifier> identifier;
  const std::vector<std::shared_ptr<Parameter>> parameters;
  const std::shared_ptr<BlockStatement> body;
};
}
}
