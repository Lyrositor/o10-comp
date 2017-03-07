#pragma once

#include <memory>

namespace comp {
  namespace ast {
    class Position {
      public:
        const size_t index;
        const size_t line;
        const size_t column;

        Position(size_t index, size_t line, size_t column);
        virtual ~Position();
    };

    class SourceLocation {
      public:
        const Position start;
        const Position end;

        SourceLocation(const Position &start, const Position &end);
        virtual ~SourceLocation();
    };
  }
}
