#include <comp/ir/builtins.h>

namespace comp {
namespace ir {
static const FunctionsTable kBuiltInFunctions = {
  {"getchar", nullptr},
  {"putchar", nullptr}
};

static const DataTypesTable kBuiltInDataTypes = {
  {"void", kVoidType},
  {"char", kCharType},
  {"int32_t", kInt32Type},
  {"int64_t", kInt64Type}
};

const SymbolTable kBuiltInSymbols(kBuiltInDataTypes, {}, kBuiltInFunctions);

RootContext CreateRootContextWithBuiltIns() {
  return RootContext(kBuiltInSymbols, {});
}
}
}
