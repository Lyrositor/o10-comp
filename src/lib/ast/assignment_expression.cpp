#include <comp/ast/assignment_expression.h>

namespace comp {
namespace ast {
std::unique_ptr<AssignmentExpression> AssignmentExpression::Create(
  std::shared_ptr<LExpression> left,
  std::shared_ptr<RExpression> right,
  AssignmentOperator op,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<AssignmentExpression>(
    new AssignmentExpression(left, right, op, location));
}
AssignmentExpression::AssignmentExpression(
  std::shared_ptr<LExpression> left,
  std::shared_ptr<RExpression> right,
  AssignmentOperator op,
  std::shared_ptr<SourceLocation> location
) :
  RExpression(Type::AssignmentExpression, location),
  left(left),
  right(right),
  op(op) {
}

AssignmentExpression::~AssignmentExpression() {
}
}  // namespace ast
}  // namespace comp
