#pragma once

#include <cstddef>
#include "./ast.h"

namespace comp {
  namespace eval {
    int32_t evalExpression(comp::ast::Expression &expression);
  }
}
