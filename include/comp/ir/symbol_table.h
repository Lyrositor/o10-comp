#pragma once

#include <string>
#include <map>
#include "data_type.h"
#include "function.h"
#include "variable.h"

namespace comp {
namespace ir {
typedef std::map<std::string, std::shared_ptr<const DataType>> DataTypesTable;
typedef std::map<std::string, std::shared_ptr<Variable>> VariablesTable;
typedef std::map<std::string, std::shared_ptr<Function>> FunctionsTable;

struct SymbolTable {
  SymbolTable();
  SymbolTable(
    DataTypesTable data_types,
    VariablesTable variables,
    FunctionsTable functions
  );

  DataTypesTable data_types;
  VariablesTable variables;
  FunctionsTable functions;
};
}
}
