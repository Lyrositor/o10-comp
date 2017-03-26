#pragma once

#include <string>

#include "comp/ast/identifier.h"
#include "comp/ast/node.h"

namespace comp {
namespace ast {
struct Declarator : public Node {
  Declarator(Type node_type, std::shared_ptr<SourceLocation> location);

  virtual ~Declarator() = 0;

  virtual std::string GetName() const = 0;
};
}  // namespace ast
}  // namespace comp
