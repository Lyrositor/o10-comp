#pragma once

namespace comp {
namespace ast {
struct Position {
  Position(size_t index, size_t line, size_t column);

  virtual ~Position();

  const size_t index;
  const size_t line;
  const size_t column;
};

struct SourceLocation {
  SourceLocation(const Position &start, const Position &end);

  virtual ~SourceLocation();

  const Position start;
  const Position end;
};
}
}
