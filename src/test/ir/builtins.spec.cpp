#include "gtest/gtest.h"
#include <comp/ir/builtins.h>

namespace comp {
namespace ir {
TEST(comp__ir__builtins, SizeOfPrimitiveTypes) {
  EXPECT_EQ(0, GetVoidType()->GetSize());
  EXPECT_EQ(4, GetInt32Type()->GetSize());
  EXPECT_EQ(8, GetInt64Type()->GetSize());
  EXPECT_EQ(1, GetCharType()->GetSize());
}

TEST(comp__ir__builtins, resolveBuiltinTypes) {
  RootContext context = CreateRootContextWithBuiltIns();
  std::shared_ptr<const DataType> void_type = context.ResolveDataType("void");
  std::shared_ptr<const DataType> int32_type = context.ResolveDataType("int32_t");
  std::shared_ptr<const DataType> int64_type = context.ResolveDataType("int64_t");
  std::shared_ptr<const DataType> char_type = context.ResolveDataType("char");
  EXPECT_EQ(GetVoidType(), void_type);
  EXPECT_EQ(GetInt32Type(), int32_type);
  EXPECT_EQ(GetInt64Type(), int64_type);
  EXPECT_EQ(GetCharType(), char_type);
}
}
}
