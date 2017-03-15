#pragma once

#include <cstddef>

namespace comp {
namespace ast {
struct Position final {
  Position(size_t index, size_t line, size_t column);

  ~Position();

  const size_t index;
  const size_t line;
  const size_t column;
};

struct SourceLocation final {
  SourceLocation(const Position &start, const Position &end);

  ~SourceLocation();

  const Position start;
  const Position end;
};
}
}
