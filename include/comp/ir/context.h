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
class ChildContext;

/**
 * A context contains both symbols table and set of anonymous variables in a given scope.
 * In the future, it may also contain flags such as `inFunctionBody`, `inTryBlock`, etc.
 */
class Context {
 public:
  Context();
  Context(
    std::map<std::string, std::shared_ptr<DataType>> dataTypesTable,
    std::map<std::string, std::shared_ptr<Variable>> variablesTable,
    std::map<std::string, std::shared_ptr<Function>> functionsTable,
    std::set<std::shared_ptr<Variable>> variables
  );

  void registerDataType(const std::string name, std::shared_ptr<DataType> dataType);
  void registerVariable(const std::string name, std::shared_ptr<Variable> variable);
  void registerFunction(const std::string name, std::shared_ptr<Function> function);
  std::shared_ptr<Variable> createVariable(std::shared_ptr<const DataType> dataType);
  /**
   * @return The set of allocated variables
   */
  std::set<std::shared_ptr<Variable>> getVariables() const;

  /**
   * Resolve the `DataType` instance named `name` in the current context.
   *
   * It traverses the chain of parent contexts and returns the first matched DataType.
   *
   * @param name Name of the dataType
   * @return `DataType` instance named `name` in the current context.
   * @throw {std::runtime_exception} "Unkown dataType" If the dataType is not found.
   */
  virtual std::shared_ptr<DataType> resolveDataType(const std::string &name) const = 0;
  virtual std::shared_ptr<Function> resolveFunction(const std::string &name) const = 0;
  virtual std::shared_ptr<Variable> resolveVariable(const std::string &name) const = 0;

  /**
   * Forks parentContext by creating a new child context.
   *
   * This is an alias for `Context::create(parentContext`
   *
   * @return A new child context
   */
  std::unique_ptr<ChildContext> fork();

  /**
   * Joins the provided child context into the current context.
   * The provided child context must be a direct child of the current context (for example, created by `fork`)
   *
   * All the variables set of the provided child context will be merged with the one of the current context.
   * The symbols table won't be merged.
   * The provided source context will be deleted.
   *
   * @param childContext The child context to join into this context.
   */
  void join(std::unique_ptr<ChildContext> childContext);

  virtual ~Context() = 0;

 protected:
  /**
   * Named dataTypes
   */
  std::map<std::string, std::shared_ptr<DataType>> dataTypesTable;
  /**
   * Named variables
   */
  std::map<std::string, std::shared_ptr<Variable>> variablesTable;
  /**
   * Named functions
   */
  std::map<std::string, std::shared_ptr<Function>> functionsTable;
  /**
   * Shadowed and anonymous variables.
   */
  std::set<std::shared_ptr<Variable>> variables;
};

class RootContext final : public Context {
 public:
  static std::unique_ptr<RootContext> create();
  static std::unique_ptr<RootContext> create(
    std::map<std::string, std::shared_ptr<DataType>> dataTypesTable,
    std::map<std::string, std::shared_ptr<Variable>> variablesTable,
    std::map<std::string, std::shared_ptr<Function>> functionsTable,
    std::set<std::shared_ptr<Variable>> variables
  );

  RootContext();
  RootContext(
    std::map<std::string, std::shared_ptr<DataType>> dataTypesTable,
    std::map<std::string, std::shared_ptr<Variable>> variablesTable,
    std::map<std::string, std::shared_ptr<Function>> functionsTable,
    std::set<std::shared_ptr<Variable>> variables
  );

  std::shared_ptr<DataType> resolveDataType(const std::string &name) const;
  std::shared_ptr<Function> resolveFunction(const std::string &name) const;
  std::shared_ptr<Variable> resolveVariable(const std::string &name) const;

  ~RootContext();
};

class ChildContext final : public Context {
 public:
  static std::unique_ptr<ChildContext> create(Context &parentContext);
  static std::unique_ptr<ChildContext> create(
    Context &parentContext,
    std::map<std::string, std::shared_ptr<DataType>> dataTypesTable,
    std::map<std::string, std::shared_ptr<Variable>> variablesTable,
    std::map<std::string, std::shared_ptr<Function>> functionsTable,
    std::set<std::shared_ptr<Variable>> variables
  );

  ChildContext(Context &parentContext);
  ChildContext(
    Context &parentContext,
    std::map<std::string, std::shared_ptr<DataType>> dataTypesTable,
    std::map<std::string, std::shared_ptr<Variable>> variablesTable,
    std::map<std::string, std::shared_ptr<Function>> functionsTable,
    std::set<std::shared_ptr<Variable>> variables
  );

  std::shared_ptr<DataType> resolveDataType(const std::string &name) const;
  std::shared_ptr<Function> resolveFunction(const std::string &name) const;
  std::shared_ptr<Variable> resolveVariable(const std::string &name) const;

  ~ChildContext();
 protected:
  Context &parentContext;
};
}
}
