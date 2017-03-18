#include <comp/ast.h>
#include <comp/eval.h>

#include "gtest/gtest.h"

namespace comp {
namespace ast {
TEST(Ast, example) {
  std::shared_ptr<Int64Literal> lit1 = Int64Literal::Create(23, nullptr);
  std::shared_ptr<Int64Literal> lit2 = Int64Literal::Create(33, nullptr);

  EXPECT_EQ(23, lit1->value);
  EXPECT_EQ(33, lit2->value);

  std::shared_ptr<BinaryExpression> expr = BinaryExpression::Create(
    BinaryOperator::Addition,
    lit1,
    lit2,
    nullptr);

  EXPECT_EQ(lit1, expr->left);
  EXPECT_EQ(lit2, expr->right);

  EXPECT_EQ(56, comp::eval::eval_expression(*expr));
}
}  // namespace ast
}  // namespace comp
