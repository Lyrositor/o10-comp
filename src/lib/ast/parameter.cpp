#include <comp/ast/parameter.h>
#include <comp/ast/data_type.h>

namespace comp {
namespace ast {
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
