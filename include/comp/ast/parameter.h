#pragma once

#include "ctype.h"
#include "declaration.h"
#include "identifier.h"

namespace comp {
namespace ast {
struct Parameter final : public Node {
  Parameter(Type type, Identifier identifier);
  virtual ~Parameter();

  const Type type;
  const std::shared_ptr<Identifier> identifier;
};
}
}
