#include <comp/eval.h>
#include <stdexcept>

namespace comp {
namespace eval {

int32_t evalLiteral(comp::ast::Literal &expression) {
  return expression.value;
}

int32_t evalBinaryExpression(comp::ast::BinaryExpression &expression) {
  int32_t left = eval_expression(*expression.left);
  int32_t right = eval_expression(*expression.right);

  switch (expression.op) {
    case comp::ast::AdditionOperator:return left + right;
    case comp::ast::SubtractionOperator:return left - right;
    case comp::ast::MultiplicationOperator:return left * right;
    case comp::ast::DivisionOperator:return left / right;
    case comp::ast::RemainderOperator:return left % right;
    default:throw std::domain_error("Unexpected binary operator");
  }
}

int32_t eval_expression(comp::ast::Expression &expression) {
  switch (expression.type) {
    case comp::ast::NodeType::Literal:return evalLiteral(static_cast<comp::ast::Literal &>(expression));
    case comp::ast::NodeType::BinaryExpression:return evalBinaryExpression(static_cast<comp::ast::BinaryExpression &>(expression));
    default:throw std::domain_error("Unexpected expression type");
  }
}
}
}
