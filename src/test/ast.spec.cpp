#include "gtest/gtest.h"
#include <comp/ast.h>

TEST(Ast, example) {
  EXPECT_EQ(2, comp::ast::create_node());
}
