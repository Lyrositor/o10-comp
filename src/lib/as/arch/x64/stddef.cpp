#include <comp/as/arch/x64/stddef.h>

#include <unordered_map>
#include <comp/exceptions.h>

namespace comp {
namespace as {
namespace arch {
namespace x64 {
static const std::unordered_map<ir::DataType::Type, int64_t> kDataTypeSizes = {
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
    default:
      try {
        return kDataTypeSizes.at(data_type->GetType());
      } catch (std::out_of_range &e) {
        throw Exception("Invalid IR data type");
      }
  }
}
}  // namespace x64
}  // namespace arch
}  // namespace as
}  // namespace comp
