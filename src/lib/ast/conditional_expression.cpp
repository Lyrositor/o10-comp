#include <comp/ast/conditional_expression.h>

namespace comp {
namespace ast {
std::unique_ptr<ConditionalExpression> ConditionalExpression::Create(
  std::shared_ptr<RExpression> test,
  std::shared_ptr<RExpression> consequence,
  std::shared_ptr<RExpression> alternative,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<ConditionalExpression>(
    new ConditionalExpression(test, consequence, alternative, location));
}

ConditionalExpression::ConditionalExpression(
  std::shared_ptr<RExpression> test,
  std::shared_ptr<RExpression> consequence,
  std::shared_ptr<RExpression> alternative,
  std::shared_ptr<SourceLocation> location
) :
  RExpression(Type::ConditionalExpression, location),
  test(test),
  consequence(consequence),
  alternative(alternative) {
}

ConditionalExpression::~ConditionalExpression() {
}
}  // namespace ast
}  // namespace comp
