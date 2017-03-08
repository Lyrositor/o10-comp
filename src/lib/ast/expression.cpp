#include <comp/ast/expression.h>

namespace comp {
namespace ast {
Expression::Expression(NodeType type_, std::shared_ptr<SourceLocation> location_) :
    Node(type_, location_) {}
Expression::~Expression() {}
}
}
