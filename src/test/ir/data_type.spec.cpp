#include "gtest/gtest.h"
#include <comp/ir/data_type.h>

TEST(comp__ir__DataType, SizeOfPrimitiveTypes) {
  EXPECT_EQ(0, comp::ir::kVoidType->GetSize());
  EXPECT_EQ(4, comp::ir::kInt32Type->GetSize());
  EXPECT_EQ(8, comp::ir::kInt64Type->GetSize());
  EXPECT_EQ(1, comp::ir::kCharType->GetSize());
}

TEST(comp__ir__DataType, ArraySize) {
  const comp::ir::ArrayDataType integersArrayType(comp::ir::kInt32Type, 10);
  EXPECT_EQ(40, integersArrayType.GetSize());
}
