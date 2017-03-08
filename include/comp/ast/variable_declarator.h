#pragma once

#include "expression.h"
#include "identifier.h"
#include "node.h"

namespace comp {
namespace ast {
struct VariableDeclarator : public Node {
  VariableDeclarator(
    std::shared_ptr<Identifier> identifier,
    size_t array,
    std::unique_ptr<Expression> initial_value
  );  // TODO Handle int a[], b
  ~VariableDeclarator();

  const std::shared_ptr<Identifier> identifier;
  const size_t array;
  const std::unique_ptr<Expression> initial_value;
};
}
}

