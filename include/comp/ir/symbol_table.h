#pragma once

#include <string>
#include <map>
#include "data_type.h"
#include "function.h"
#include "variable.h"

namespace comp {
namespace ir {
struct SymbolTable {
  SymbolTable();
  SymbolTable(
    std::map<std::string, std::shared_ptr<DataType>> data_types,
    std::map<std::string, std::shared_ptr<Variable>> variables,
    std::map<std::string, std::shared_ptr<Function>> functions
  );

  std::map<std::string, std::shared_ptr<DataType>> data_types;
  std::map<std::string, std::shared_ptr<Variable>> variables;
  std::map<std::string, std::shared_ptr<Function>> functions;
};
}
}
