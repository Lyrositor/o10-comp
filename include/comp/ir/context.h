#pragma  once

#include <memory>
#include <string>
#include <map>
#include <set>
#include "data_type.h"
#include "function.h"
#include "variable.h"

namespace comp {
namespace ir {
/**
 * A context contains both symbols table and set of anonymous variables in a given scope.
 */
class Context {
 public:
  Context(std::shared_ptr<Context> parentContext);
  Context(
    std::shared_ptr<Context> parentContext,
    std::map<std::string, std::shared_ptr<DataType>> dataTypesTable,
    std::map<std::string, std::shared_ptr<Variable>> variablesTable,
    std::map<std::string, std::shared_ptr<Function>> functionsTable,
    std::set<std::shared_ptr<Variable>> variables
  );
  std::shared_ptr<DataType> resolveDataType(std::string &name) const;
  std::shared_ptr<Function> resolveFunction(std::string &name) const;
  std::shared_ptr<Variable> resolveVariable(std::string &name) const;
  void registerDataType(std::string name, std::shared_ptr<DataType> dataType);
  void registerVariable(std::string name, std::shared_ptr<Variable> variable);
  void registerFunction(std::string name, std::shared_ptr<Function> function);
  std::shared_ptr<Variable> createVariable(std::shared_ptr<DataType> dataType);
  virtual ~Context();
 private:
  std::shared_ptr<const Context> parentContext;
  std::map<std::string, std::shared_ptr<DataType>> dataTypesTable;
  std::map<std::string, std::shared_ptr<Variable>> variablesTable;
  std::map<std::string, std::shared_ptr<Function>> functionsTable;
  /**
   * Shadowed and anonymous variables.
   */
  std::set<std::shared_ptr<Variable>> variables;
};
}
}
