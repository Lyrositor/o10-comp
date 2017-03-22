#include <comp/ast/parameter.h>

namespace comp {
namespace ast {
std::unique_ptr<Parameter> Parameter::Create(
  std::shared_ptr<LiteralDataType> data_type,
  std::shared_ptr<Declarator> declarator,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<Parameter>(
    new Parameter(data_type, declarator, location));
}

Parameter::Parameter(
  std::shared_ptr<LiteralDataType> data_type,
  std::shared_ptr<Declarator> declarator,
  std::shared_ptr<SourceLocation> location
) :
  Node(Type::Parameter, location),
  data_type(data_type),
  declarator(declarator) {
}

Parameter::~Parameter() {
}
}  // namespace ast
}  // namespace comp
