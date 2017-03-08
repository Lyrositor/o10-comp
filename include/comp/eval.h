#pragma once

#include <cstddef>
#include "ast.h"

namespace comp {
namespace eval {
int32_t eval_expression(comp::ast::Expression &expression);
}
}
