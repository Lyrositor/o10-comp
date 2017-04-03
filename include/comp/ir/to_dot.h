#pragma once

#include <memory>
#include "comp/dot/ast/graph.h"
#include "comp/ir/program.h"

namespace comp {
namespace ir {
std::unique_ptr<dot::ast::Graph> ProgramToDot(const Program &node);
}
}
