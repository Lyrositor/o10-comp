#include <comp/ast/data_type.h>
#include <comp/ast/function.h>

namespace comp {
namespace ast {
std::unique_ptr<Function> Function::Create(
  std::shared_ptr<Identifier> identifier,
  std::vector<std::shared_ptr<Parameter>> parameters,
  std::shared_ptr<DataType> return_type,
  std::shared_ptr<BlockStatement> body,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<Function>(
    new Function(identifier, parameters, return_type, body, location));
}

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
}  // namespace ast
}  // namespace comp
