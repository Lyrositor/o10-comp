#pragma once

#include <memory>
#include "comp/dot/ast.h"
#include "comp/ir/program.h"

namespace comp {
namespace ir {
std::unique_ptr<dot::ast::Graph> ProgramToDot(const Program &node);
}
}
