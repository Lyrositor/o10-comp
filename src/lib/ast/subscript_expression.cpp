#include <comp/ast/subscript_expression.h>

namespace comp {
namespace ast {
std::unique_ptr<SubscriptExpression> SubscriptExpression::Create(
  std::shared_ptr<RExpression> array,
  std::shared_ptr<RExpression> index,
  std::shared_ptr<SourceLocation> location) {
  return std::unique_ptr<SubscriptExpression>(
    new SubscriptExpression(array, index, location));
}

SubscriptExpression::SubscriptExpression(
  std::shared_ptr<RExpression> array,
  std::shared_ptr<RExpression> index,
  std::shared_ptr<SourceLocation> location
) :
  LExpression(Type::SubscriptExpression, location),
  array(array),
  index(index) {
}

SubscriptExpression::~SubscriptExpression() {
}
}  // namespace ast
}  // namespace comp
