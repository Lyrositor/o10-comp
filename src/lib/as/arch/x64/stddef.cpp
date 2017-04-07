#include <comp/as/arch/x64/stddef.h>

#include <unordered_map>

#include <comp/utils.h>

namespace comp {
namespace as {
namespace arch {
namespace x64 {
static const std::unordered_map<ir::DataType::Type, int64_t, EnumClassHash>
  kDataTypeSizes = {
  {ir::DataType::Type::Void, 0},
  {ir::DataType::Type::Uint8, 1},
  {ir::DataType::Type::Int32, 4},
  {ir::DataType::Type::Int64, 8},
  {ir::DataType::Type::Pointer, 8}
};

int64_t GetDataTypeSize(std::shared_ptr<const ir::DataType> data_type) {
  switch (data_type->GetType()) {
    case ir::DataType::Type::Array: {
      std::shared_ptr<const ir::ArrayDataType>
        array = std::static_pointer_cast<const ir::ArrayDataType>(
        data_type);
      return GetDataTypeSize(array->GetItemType()) * array->GetSize();
    }
    case ir::DataType::Type::Int32:
    case ir::DataType::Type::Int64:
    case ir::DataType::Type::Pointer:
    case ir::DataType::Type::Uint8:
    case ir::DataType::Type::Void:
      try {
        return kDataTypeSizes.at(data_type->GetType());
      } catch (std::out_of_range &e) {
        throw Exception("invalid IR data type");
      }
  }
  throw Exception("unexpected IR data type");
}
}  // namespace x64
}  // namespace arch
}  // namespace as
}  // namespace comp
