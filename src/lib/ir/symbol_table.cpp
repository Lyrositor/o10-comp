#include <comp/ir/symbol_table.h>

namespace comp {
namespace ir {
SymbolTable::SymbolTable() {
}

SymbolTable::SymbolTable(
  DataTypesTable data_types,
  VariablesTable variables,
  FunctionsTable functions
) :
  data_types(std::move(data_types)),
  variables(std::move(variables)),
  functions(std::move(functions)) {
}
}  // namespace ir
}  // namespace comp
