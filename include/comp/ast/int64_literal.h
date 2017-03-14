#pragma once

#include <cstddef>
#include "literal.h"

namespace comp {
namespace ast {
struct Int64Literal final : public Literal {
  static std::shared_ptr<Int64Literal> create(
    int64_t value,
    std::shared_ptr<SourceLocation> location = nullptr
  );

  Int64Literal(int64_t value, std::shared_ptr<SourceLocation> location);

  virtual ~Int64Literal();

  const int64_t value;
};
}
}
