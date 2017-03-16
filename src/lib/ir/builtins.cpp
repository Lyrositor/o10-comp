#include <comp/ir/builtins.h>
#include <comp/ir/function.h>

namespace comp {
namespace ir {
static const std::shared_ptr<const PrimitiveDataType> kVoidType(new PrimitiveDataType(0));

static const std::shared_ptr<const PrimitiveDataType> kCharType(new PrimitiveDataType(1));

static const std::shared_ptr<const PrimitiveDataType> kInt32Type(new PrimitiveDataType(4));

static const std::shared_ptr<const PrimitiveDataType> kInt64Type(new PrimitiveDataType(8));

static const std::shared_ptr<Function> kGetcharFunction = Function::Create(
  std::vector<std::shared_ptr<const Parameter>>(),
  kCharType
);

static const std::shared_ptr<Function> kPutcharFunction = Function::Create(
  std::vector<std::shared_ptr<const Parameter>>({Parameter::Create(kCharType, "c")}),
  kVoidType
);

static const FunctionsTable kBuiltInFunctions = {
  {"getchar", kGetcharFunction},
  {"putchar", kPutcharFunction}
};

static const DataTypesTable kBuiltInDataTypes = {
  {"void", kVoidType},
  {"char", kCharType},
  {"int32_t", kInt32Type},
  {"int64_t", kInt64Type}
};

const SymbolTable kBuiltInSymbols(kBuiltInDataTypes, {}, kBuiltInFunctions);

const std::shared_ptr<const PrimitiveDataType> GetVoidType() {
  return kVoidType;
}

const std::shared_ptr<const PrimitiveDataType> GetCharType() {
  return kCharType;
}

const std::shared_ptr<const PrimitiveDataType> GetInt32Type() {
  return kInt32Type;
}

const std::shared_ptr<const PrimitiveDataType> GetInt64Type() {
  return kInt64Type;
}

RootContext CreateRootContextWithBuiltIns() {
  return RootContext(kBuiltInSymbols, {});
}
}
}
