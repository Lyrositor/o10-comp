#include <comp/ast.h>

namespace comp {
namespace ast {
DataType::DataType(Node::Type nodeType, std::shared_ptr<SourceLocation> location) :
  DataType(nodeType, location) {}
Expression::~Expression() {}
}
}
