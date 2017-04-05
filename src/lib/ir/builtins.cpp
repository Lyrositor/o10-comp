#include <comp/ir/builtins.h>

#include <vector>

#include <comp/ir/program_symbol.h>

namespace comp {
namespace ir {
static const std::shared_ptr<const VoidDataType>
  kVoidType(new VoidDataType());

static const std::shared_ptr<const Uint8DataType>
  kUint8Type(new Uint8DataType());

static const std::shared_ptr<const Int32DataType>
  kInt32Type(new Int32DataType());

static const std::shared_ptr<const Int64DataType>
  kInt64Type(new Int64DataType());

static const std::shared_ptr<FunctionSymbol>
  kGetcharFunction = FunctionSymbol::Create(
  "getchar",
  std::vector<std::shared_ptr<const Variable>>(),
  kUint8Type
);

static const std::shared_ptr<FunctionSymbol>
  kPutcharFunction = FunctionSymbol::Create(
  "putchar",
  std::vector<std::shared_ptr<const Variable>>(
    {Variable::Create(kUint8Type, nullptr)}),
  kVoidType
);

static const FunctionsTable kBuiltInFunctions = {
  {"getchar", kGetcharFunction},
  {"putchar", kPutcharFunction}
};

static const DataTypesTable kBuiltInDataTypes = {
  {"void", kVoidType},
  {"char", kUint8Type},
  {"int32_t", kInt32Type},
  {"int64_t", kInt64Type}
};

const SymbolTable kBuiltInSymbols(kBuiltInDataTypes, {}, kBuiltInFunctions);

const std::shared_ptr<const VoidDataType> GetVoidType() {
  return kVoidType;
}

const std::shared_ptr<const Uint8DataType> GetUint8Type() {
  return kUint8Type;
}

const std::shared_ptr<const Int32DataType> GetInt32Type() {
  return kInt32Type;
}

const std::shared_ptr<const Int64DataType> GetInt64Type() {
  return kInt64Type;
}

RootContext CreateRootContextWithBuiltIns() {
  return RootContext(kBuiltInSymbols, {});
}
}  // namespace ir
}  // namespace comp
