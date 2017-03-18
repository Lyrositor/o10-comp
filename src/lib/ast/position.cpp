#include <comp/ast/position.h>

namespace comp {
namespace ast {
Position::Position(size_t index, size_t line, size_t column) :
  index(index), line(line), column(column) {
}

Position::~Position() {
}

SourceLocation::SourceLocation(const Position &start, const Position &end) :
  start(start), end(end) {
}

SourceLocation::~SourceLocation() {
}
}  // namespace ast
}  // namespace comp
