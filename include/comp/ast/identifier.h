#pragma once

#include "expression.h"

namespace comp {
namespace ast {
struct Identifier final : public Expression {
  Identifier(std::string name, std::shared_ptr<SourceLocation> location = nullptr);

  virtual ~Identifier();

  const std::string name;
};
}
}
