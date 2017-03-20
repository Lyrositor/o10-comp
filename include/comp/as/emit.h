#pragma once

#include <ostream>
#include "comp/as/ast/program.h"

namespace comp {
namespace as {
/**
 * Serialize the provided `node` and write it to `out`.
 *
 * The generated assembly code will use the AT&T syntax.
 */
void emitProgram(ast::Program node, std::ostream out);
}
}
