#pragma once

#include "node.h"
namespace comp {
namespace ast {
struct Statement : public Node {
  Statement();
  virtual ~Statement() = 0;
};
}
}
