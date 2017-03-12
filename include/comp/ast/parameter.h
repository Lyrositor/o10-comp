#pragma once

#include "ctype.h"
#include "declaration.h"
#include "identifier.h"

namespace comp {
namespace ast {
struct Parameter final : public Node {
  Parameter(std::shared_ptr<Type> type, Identifier identifier);
  virtual ~Parameter();

  const std::shared_ptr<Type> type;
  const std::shared_ptr<Identifier> identifier;
};
}
}
