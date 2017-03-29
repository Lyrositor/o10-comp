#include <comp/ast/position.h>
#include <memory>

#include <comp/parser/parser_config.h>

namespace comp {
namespace ast {
Position::Position(size_t index, size_t line, size_t column) :
  index(index), line(line), column(column) {
}

Position::~Position() {
}

std::shared_ptr<SourceLocation> SourceLocation::Create(
  const YYLTYPE *yylloc
) {
  return std::unique_ptr<SourceLocation>(new SourceLocation(
    Position(yylloc->first_index, yylloc->first_line, yylloc->first_column),
    Position(yylloc->last_index, yylloc->last_line, yylloc->last_column)
  ));
}

SourceLocation::SourceLocation(const Position &start, const Position &end) :
  start(start), end(end) {
}

SourceLocation::~SourceLocation() {
}
}  // namespace ast
}  // namespace comp
