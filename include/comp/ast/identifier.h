#pragma once

#include "expression.h"
namespace comp {
namespace ast {
struct Identifier : public Expression {
  Identifier(std::string name);

  const std::string name;
};
}
}
