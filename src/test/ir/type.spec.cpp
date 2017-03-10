#include "gtest/gtest.h"
#include <comp/ir/type.h>

TEST(Type, SizeOfPrimitiveTypes) {
  EXPECT_EQ(0, comp::ir::voidType.getSize());
  EXPECT_EQ(4, comp::ir::int32Type.getSize());
  EXPECT_EQ(8, comp::ir::int64Type.getSize());
  EXPECT_EQ(1, comp::ir::charType.getSize());
}

//TEST(Type, ArraySize) {
//  const comp::ir::ArrayType integersArrayType(comp::ir::int32TypePointer, 10);
//  EXPECT_EQ(40, integersArrayType.getSize());
//}
