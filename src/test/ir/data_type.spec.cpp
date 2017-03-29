#include "gtest/gtest.h"
#include <comp/ir/data_type.h>
#include <comp/ir/builtins.h>

TEST(comp__ir__DataType, ArraySize) {
  const comp::ir::ArrayDataType integersArrayType(comp::ir::GetInt32Type(), 10);
  EXPECT_EQ(10U, integersArrayType.GetSize());
}
