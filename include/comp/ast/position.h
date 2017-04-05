#pragma once

#include <cstddef>
#include <memory>

struct YYLTYPE;

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
  static std::shared_ptr<SourceLocation> Create(const YYLTYPE *yylloc);
  static std::shared_ptr<SourceLocation> Create(
    const Position &start,
    const Position &end);
  SourceLocation(const Position &start, const Position &end);

  ~SourceLocation();

  const Position start;
  const Position end;
};
}  // namespace ast
}  // namespace comp
