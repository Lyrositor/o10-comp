#include "gtest/gtest.h"
#include <comp/ir/data_type.h>
#include <comp/ir/variable.h>

TEST(comp__ir__Variable, getType) {
  // Create a variable of type int64
  comp::ir::Variable intVariable(comp::ir::int64Type);
  EXPECT_EQ(comp::ir::int64Type, intVariable.getDataType());
}
