#include <comp/ast/data_type.h>

namespace comp {
namespace ast {
DataType::DataType(Type node_type, std::shared_ptr<SourceLocation> location) :
  Node(node_type, location) {
}

DataType::~DataType() {
}
}  // namespace ast
}  // namespace comp
