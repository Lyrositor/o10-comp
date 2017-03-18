#include <comp/eval.h>
#include <stdexcept>

namespace comp {
namespace eval {

int64_t evalInt64Literal(comp::ast::Int64Literal &expression) {
  return expression.value;
}

int64_t evalBinaryExpression(comp::ast::BinaryExpression &expression) {
  int64_t left = eval_expression(*expression.left);
  int64_t right = eval_expression(*expression.right);

  switch (expression.op) {
    case comp::ast::BinaryOperator::Addition:return left + right;
    case comp::ast::BinaryOperator::Subtraction:return left - right;
    case comp::ast::BinaryOperator::Multiplication:return left * right;
    case comp::ast::BinaryOperator::Division:return left / right;
    case comp::ast::BinaryOperator::Remainder:return left % right;
    default:throw std::domain_error("Unexpected binary operator");
  }
}

int64_t eval_expression(comp::ast::RExpression &expression) {
  switch (expression.node_type) {
    case comp::ast::Node::Type::Int64Literal: {
      return evalInt64Literal(static_cast<comp::ast::Int64Literal &>(expression));
    }
    case comp::ast::Node::Type::BinaryExpression: {
      return evalBinaryExpression(static_cast<comp::ast::BinaryExpression &>(expression));
    }
    default: {
      throw std::domain_error("Unexpected expression type");
    }
  }
}
}
}
