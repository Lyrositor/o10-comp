#pragma once

#include "comp/ast/statement.h"

namespace comp {
namespace ast {
struct Declaration : public Statement {
  Declaration(Type node_type, std::shared_ptr<SourceLocation> location);

  virtual ~Declaration() = 0;
};
}  // namespace ast
}  // namespace comp
