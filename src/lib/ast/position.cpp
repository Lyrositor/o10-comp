#include <comp/ast/position.h>
#include <memory>

namespace comp {
namespace ast {
Position::Position(size_t index, size_t line, size_t column) :
  index(index), line(line), column(column) {
}

Position::~Position() {
}

std::shared_ptr<SourceLocation> SourceLocation::Create(
  size_t start_index,
  size_t start_line,
  size_t start_column,
  size_t end_index,
  size_t end_line,
  size_t end_column) {
  return std::unique_ptr<SourceLocation>(new SourceLocation(
    Position(start_index, start_line, start_column),
    Position(end_index, end_line, end_column)
  ));
}

SourceLocation::SourceLocation(const Position &start, const Position &end) :
  start(start), end(end) {
}

SourceLocation::~SourceLocation() {
}
}  // namespace ast
}  // namespace comp
