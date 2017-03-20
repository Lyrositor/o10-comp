#pragma once

#include "comp/ir/context.h"

namespace comp {
namespace ir {
const std::shared_ptr<const PrimitiveDataType> GetVoidType();

const std::shared_ptr<const PrimitiveDataType> GetCharType();

const std::shared_ptr<const PrimitiveDataType> GetInt32Type();

const std::shared_ptr<const PrimitiveDataType> GetInt64Type();

RootContext CreateRootContextWithBuiltIns();
}  // namespace ir
}  // namespace comp
