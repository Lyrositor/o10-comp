#pragma once

#include <memory>
#include <vector>
#include "comp/dot/ast/node.h"

namespace comp {
namespace dot {
namespace ast {
struct Assignment final : Node {
  static std::unique_ptr<Assignment> Create(
    std::string key,
    std::string value);

  Assignment(
    std::string key,
    std::string value);
  ~Assignment();

  const std::string key;
  const std::string value;
};
}  // namespace ast
}  // namespace dot
}  // namespace comp
