#include <comp/ast.h>

namespace comp {
namespace ast {
LiteralDataType::LiteralDataType(std::shared_ptr<Identifier> identifier, std::shared_ptr<SourceLocation> location) :
  DataType(Node::Type::LiteralDataType, location), identifier(identifier) {}
ArrayDataType::~ArrayDataType() {}
}
}
