#include <comp/ast/expression.h>

namespace comp {
namespace ast {
LExpression::LExpression(
  Type node_type,
  std::shared_ptr<SourceLocation> location
) : RExpression(node_type, location) {
}

LExpression::~LExpression() {
}

RExpression::RExpression(
  Type node_type,
  std::shared_ptr<SourceLocation> location
) : Node(node_type, location) {
}

RExpression::~RExpression() {
}
}  // namespace ast
}  // namespace comp
