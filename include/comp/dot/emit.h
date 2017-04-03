#pragma once

#include <ostream>
#include "comp/dot/ast.h"

namespace comp {
namespace dot {
void EmitGraph(const ast::Graph &node, std::ostream &out);
}  // namespace dot
}  // namespace comp
