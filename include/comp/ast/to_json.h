#pragma once

#include <memory>
#include <rapidjson/document.h>
#include "comp/ast.h"

namespace comp {
namespace ast {
std::unique_ptr<rapidjson::Document> ProgramToJson(const Program &node);
}  // namespace ast
}  // namespace comp
