#include <comp/ast/identifier_data_type.h>

namespace comp {
namespace ast {
std::unique_ptr<IdentifierDataType> IdentifierDataType::Create(
  std::shared_ptr<Identifier> identifier,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<IdentifierDataType>(
    new IdentifierDataType(identifier, location));
}

IdentifierDataType::IdentifierDataType(
  std::shared_ptr<Identifier> identifier,
  std::shared_ptr<SourceLocation> location
) : DataType(Type::IdentifierDataType, location), identifier(identifier) {
}

IdentifierDataType::~IdentifierDataType() {
}
}  // namespace ast
}  // namespace comp
