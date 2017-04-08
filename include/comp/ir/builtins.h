#pragma once

#include "comp/ir/context.h"

namespace comp {
namespace ir {
const std::shared_ptr<const VoidDataType> GetVoidType();

const std::shared_ptr<const Uint8DataType> GetUint8Type();

const std::shared_ptr<const Int32DataType> GetInt32Type();

const std::shared_ptr<const Int64DataType> GetInt64Type();

/**
 * Return a type representin an unsigned integer with a size
 * depending on the target architecture (64 bits for `x64`).
 */
const std::shared_ptr<const Int64DataType> GetUsizeType();

RootContext CreateRootContextWithBuiltIns();
}  // namespace ir
}  // namespace comp
