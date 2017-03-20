#include <comp/ast/call_expression.h>

namespace comp {
namespace ast {
std::unique_ptr<CallExpression> CallExpression::Create(
  std::shared_ptr<RExpression> callee,
  std::vector<std::shared_ptr<RExpression>> arguments,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<CallExpression>(
    new CallExpression(callee, arguments, location));
}

CallExpression::CallExpression(
  std::shared_ptr<RExpression> callee,
  std::vector<std::shared_ptr<RExpression>> arguments,
  std::shared_ptr<SourceLocation> location
) :
  RExpression(Type::CallExpression, location),
  callee(callee),
  arguments(arguments) {
}

CallExpression::~CallExpression() {
}
}  // namespace ast
}  // namespace comp
