#pragma once

#include "expression.h"
#include "identifier.h"
#include "node.h"

namespace comp {
namespace ast {
struct VariableDeclarator final : public Node {
  static std::unique_ptr<VariableDeclarator> Create(
    std::shared_ptr<Identifier> identifier,
    std::shared_ptr<Expression> initial_value,
    std::shared_ptr<SourceLocation> location = nullptr
  );

  VariableDeclarator(
    std::shared_ptr<Identifier> identifier,
    std::shared_ptr<Expression> initial_value,
    std::shared_ptr<SourceLocation> location = nullptr
  );  // TODO Handle int a[], b

  ~VariableDeclarator();

  const std::shared_ptr<Identifier> identifier;
  const std::shared_ptr<Expression> initial_value;
};
}
}
