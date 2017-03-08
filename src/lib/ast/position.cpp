#include <comp/ast/position.h>

namespace comp {
namespace ast {
Position::Position(size_t index_, size_t line_, size_t column_) :
    index(index_), line(line_), column(column_) {}
Position::~Position() {}

SourceLocation::SourceLocation(const Position &start_, const Position &end_) :
    start(start_), end(end_) {}
SourceLocation::~SourceLocation() {}
}
}
