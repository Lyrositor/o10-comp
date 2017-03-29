#pragma once

#include <cstddef>
#include <memory>

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
  static std::shared_ptr<SourceLocation> Create(
    size_t start_index,
    size_t start_line,
    size_t start_column,
    size_t end_index,
    size_t end_line,
    size_t end_column);
  SourceLocation(const Position &start, const Position &end);

  ~SourceLocation();

  const Position start;
  const Position end;
};
}  // namespace ast
}  // namespace comp
