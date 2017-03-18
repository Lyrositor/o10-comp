#include <comp/ast/assignment_expression.h>

namespace comp {
namespace ast {
std::unique_ptr<AssignmentExpression> AssignmentExpression::Create(
  std::shared_ptr<LExpression> lvalue,
  std::shared_ptr<RExpression> rvalue,
  BinaryOperator op,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<AssignmentExpression>(
    new AssignmentExpression(lvalue, rvalue, op, location));
}
AssignmentExpression::AssignmentExpression(
  std::shared_ptr<LExpression> lvalue,
  std::shared_ptr<RExpression> rvalue,
  BinaryOperator op,
  std::shared_ptr<SourceLocation> location
) :
  RExpression(Type::AssignmentExpression, location),
  lvalue(lvalue),
  rvalue(rvalue),
  op(op) {
}

AssignmentExpression::~AssignmentExpression() {
}
}  // namespace ast
}  // namespace comp
