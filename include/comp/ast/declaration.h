#pragma once

#include "statement.h"

namespace comp {
namespace ast {
struct Declaration : public Statement {
  Declaration(Node::Type nodeType, std::shared_ptr<SourceLocation> location);

  virtual ~Declaration() = 0;
};
}
}
