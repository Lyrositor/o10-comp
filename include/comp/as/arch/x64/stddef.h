#pragma once

#include <cstdint>

#include <comp/ir/data_type.h>

namespace comp {
namespace as {
namespace arch {
namespace x64 {
const int64_t kRegisterSize = 8;

int64_t GetDataTypeSize(std::shared_ptr<const ir::DataType> data_type);
}  // namespace x64
}  // namespace arch
}  // namespace as
}  // namespace comp
