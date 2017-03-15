#pragma once

#include <string>
#include "expression.h"

namespace comp {
namespace ast {
struct Identifier final : public Expression {
  static std::unique_ptr<Identifier> Create(std::string name, std::shared_ptr<SourceLocation> location = nullptr);
  
  Identifier(std::string name, std::shared_ptr<SourceLocation> location = nullptr);

  ~Identifier();

  const std::string name;
};
}
}
