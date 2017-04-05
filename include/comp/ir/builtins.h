#pragma once

#include "comp/ir/context.h"

namespace comp {
namespace ir {
const std::shared_ptr<const VoidDataType> GetVoidType();

const std::shared_ptr<const Uint8DataType> GetUint8Type();

const std::shared_ptr<const Int32DataType> GetInt32Type();

const std::shared_ptr<const Int64DataType> GetInt64Type();

RootContext CreateRootContextWithBuiltIns();
}  // namespace ir
}  // namespace comp
