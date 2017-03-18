#include <comp/ast/literal_data_type.h>

namespace comp {
namespace ast {
std::unique_ptr<LiteralDataType> LiteralDataType::Create(
  std::shared_ptr<Identifier> identifier,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<LiteralDataType>(
    new LiteralDataType(identifier, location));
}

LiteralDataType::LiteralDataType(
  std::shared_ptr<Identifier> identifier,
  std::shared_ptr<SourceLocation> location
) : DataType(Type::LiteralDataType, location), identifier(identifier) {
}

LiteralDataType::~LiteralDataType() {
}
}  // namespace ast
}  // namespace comp
