#pragma once

#include "ctype.h"
#include "declaration.h"
#include "identifier.h"

namespace comp {
namespace ast {
struct Parameter : public Node {
  Parameter(CType type, Identifier identifier);
  virtual ~Parameter();

  const CType type;
  const std::shared_ptr<Identifier> identifier;
};
}
}
