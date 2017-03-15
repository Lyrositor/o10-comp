#include <comp/ir/symbol_table.h>

namespace comp {
namespace ir {
SymbolTable::SymbolTable() :
  data_types(std::map<std::string, std::shared_ptr<DataType>>()),
  variables(std::map<std::string, std::shared_ptr<Variable>>()),
  functions(std::map<std::string, std::shared_ptr<Function>>()) {
}

SymbolTable::SymbolTable(
  std::map<std::string, std::shared_ptr<DataType>> data_types,
  std::map<std::string, std::shared_ptr<Variable>> variables,
  std::map<std::string, std::shared_ptr<Function>> functions
) :
  data_types(std::move(data_types)),
  variables(std::move(variables)),
  functions(std::move(functions)) {
}
}
}
