#include <comp/ast/parameter.h>

namespace comp {
namespace ast {
Parameter::Parameter(Type node_type, std::shared_ptr<SourceLocation> location) :
  Node(node_type, location) {
}

Parameter::~Parameter() {
}

std::unique_ptr<NamedParameter> NamedParameter::Create(
  std::shared_ptr<IdentifierDataType> data_type,
  std::shared_ptr<Declarator> declarator,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<NamedParameter>(
    new NamedParameter(data_type, declarator, location));
}

NamedParameter::NamedParameter(
  std::shared_ptr<IdentifierDataType> data_type,
  std::shared_ptr<Declarator> declarator,
  std::shared_ptr<SourceLocation> location
) :
  Parameter(Type::NamedParameter, location),
  data_type(data_type),
  declarator(declarator) {
}

NamedParameter::~NamedParameter() {
}

std::unique_ptr<AnonymousParameter> AnonymousParameter::Create(
  std::shared_ptr<DataType> data_type,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<AnonymousParameter>(
    new AnonymousParameter(data_type, location));
}

AnonymousParameter::AnonymousParameter(
  std::shared_ptr<DataType> data_type,
  std::shared_ptr<SourceLocation> location
) :
  Parameter(Type::AnonymousParameter, location),
  data_type(data_type) {
}

AnonymousParameter::~AnonymousParameter() {
}
}  // namespace ast
}  // namespace comp
