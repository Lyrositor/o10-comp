#include <comp/ast/parameter.h>
#include <comp/ast/data_type.h>

namespace comp {
namespace ast {
std::unique_ptr<Parameter> Parameter::Create(
  std::shared_ptr<DataType> dataType,
  std::shared_ptr<Identifier> identifier,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<Parameter>(new Parameter(dataType, identifier, location));
}

Parameter::Parameter(
  std::shared_ptr<DataType> dataType,
  std::shared_ptr<Identifier> identifier,
  std::shared_ptr<SourceLocation> location
) :
  Node(Node::Type::Parameter, location),
  dataType(dataType),
  identifier(identifier) {
}

Parameter::~Parameter() {
}
}
}
