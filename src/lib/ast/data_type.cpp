#include <comp/ast/data_type.h>

namespace comp {
namespace ast {
DataType::DataType(Node::Type nodeType, std::shared_ptr<SourceLocation> location) :
  Node(nodeType, location) {
}

DataType::~DataType() {
}
}
}
