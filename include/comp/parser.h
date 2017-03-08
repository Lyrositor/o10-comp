#pragma once

#include <memory>
#include "ast.h"

namespace comp {
namespace parser {
// TODO: Accept istream
std::shared_ptr<comp::ast::Expression> parse();
}
}
