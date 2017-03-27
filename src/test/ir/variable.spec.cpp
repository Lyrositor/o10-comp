#include "gtest/gtest.h"
#include <comp/ir/data_type.h>
#include <comp/ir/variable.h>
#include <comp/ir/builtins.h>

TEST(comp__ir__Variable, getType) {
  // Create a variable of type int64
  comp::ir::Variable intVariable(comp::ir::GetInt64Type());
  EXPECT_EQ(comp::ir::GetInt64Type(), intVariable.GetDataType());
}
