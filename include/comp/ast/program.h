#pragma once

#include <memory>
#include <vector>
#include "declaration.h"
#include "node.h"

namespace comp {
namespace ast {
struct Program : public Node {
  Program(std::vector<std::shared_ptr<Declaration>> body);
  virtual ~Program();

  const std::vector<std::shared_ptr<Declaration>> body;
};
}
}
