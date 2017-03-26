#pragma once

#include <map>
#include <string>

#include "comp/ir/data_type.h"
#include "comp/ir/program_symbol.h"
#include "comp/ir/variable.h"

namespace comp {
namespace ir {
typedef std::map<std::string, std::shared_ptr<const DataType>> DataTypesTable;
typedef std::map<std::string, std::shared_ptr<const Variable>> VariablesTable;
typedef std::map<std::string, std::shared_ptr<FunctionSymbol>> FunctionsTable;

struct SymbolTable {
  SymbolTable();
  SymbolTable(
    DataTypesTable data_types,
    VariablesTable variables,
    FunctionsTable functions);

  DataTypesTable data_types;
  VariablesTable variables;
  FunctionsTable functions;
};
}  // namespace ir
}  // namespace comp
