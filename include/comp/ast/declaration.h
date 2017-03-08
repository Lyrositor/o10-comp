#pragma once

#include "statement.h"

namespace comp {
namespace ast {
struct Declaration : public Statement {
  Declaration(Type type, std::shared_ptr<SourceLocation> location);

  virtual ~Declaration() = 0;
};
}
}
