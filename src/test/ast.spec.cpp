#include "gtest/gtest.h"
#include <comp/ast.h>
#include <comp/eval.h>

TEST(Ast, example) {
  std::shared_ptr<comp::ast::Int64Literal> lit1 = comp::ast::Int64Literal::Create(23, nullptr);
  std::shared_ptr<comp::ast::Int64Literal> lit2 = comp::ast::Int64Literal::Create(33, nullptr);

  EXPECT_EQ(23, lit1->value);
  EXPECT_EQ(33, lit2->value);

  std::shared_ptr<comp::ast::BinaryExpression> expr = comp::ast::BinaryExpression::Create(
    comp::ast::BinaryOperator::Addition,
    lit1,
    lit2,
    nullptr
  );

  EXPECT_EQ(lit1, expr->left);
  EXPECT_EQ(lit2, expr->right);

  EXPECT_EQ(56, comp::eval::eval_expression(*expr));
}
