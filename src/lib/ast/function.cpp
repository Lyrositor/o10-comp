#include <comp/ast/data_type.h>
#include <comp/ast/function.h>

namespace comp {
namespace ast {
Function::Function(
  std::shared_ptr<Identifier> identifier,
  std::vector<std::shared_ptr<Parameter>> parameters,
  std::shared_ptr<DataType> return_type,
  std::shared_ptr<BlockStatement> body,
  std::shared_ptr<SourceLocation> location
) :
  Declaration(Node::Type::Function, location),
  identifier(identifier),
  parameters(parameters),
  return_type(return_type),
  body(body) {
}

Function::~Function() {
}
}
}
