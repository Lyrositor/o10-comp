#include "gtest/gtest.h"
#include <comp/parser.h>
#include <comp/eval.h>

TEST(Parser, example) {
  std::shared_ptr<comp::ast::Expression> expr = comp::parser::parse();
  EXPECT_EQ(579, comp::eval::evalExpression(*expr));
}
