#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>

#include "comp/ir/data_type.h"
#include "comp/ir/program_symbol.h"
#include "comp/ir/symbol_table.h"
#include "comp/ir/variable.h"

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
    SymbolTable symbols,
    std::set<std::shared_ptr<const Variable>> variables);

  virtual ~Context() = 0;

  void RegisterDataType(
    const std::string name,
    std::shared_ptr<const DataType> data_type);
  void RegisterVariable(
    const std::string name,
    std::shared_ptr<const Variable> variable);
  void RegisterFunction(
    const std::string name,
    std::shared_ptr<FunctionSymbol> function);
  std::shared_ptr<const Variable> CreateVariable(
    std::shared_ptr<const DataType> data_type,
    std::shared_ptr<const ast::Declarator> declarator);

  /**
   * @return The set of allocated variables
   */
  std::set<std::shared_ptr<const Variable>> GetVariables() const;

  /**
   * Resolve the `DataType` instance named `name` in the current context.
   *
   * It traverses the chain of parent contexts and returns the first matched DataType.
   *
   * @param name Name of the dataType
   * @return `DataType` instance named `name` in the current context.
   * @throw {std::runtime_exception} "Unknown dataType" If the dataType is not found.
   */
  virtual std::shared_ptr<const DataType> ResolveDataType(
    const std::string &name) const = 0;
  virtual std::shared_ptr<FunctionSymbol> ResolveFunction(
    const std::string &name) const = 0;
  virtual std::shared_ptr<const Variable> ResolveVariable(
    const std::string &name) const = 0;

  /**
   * Forks parentContext by creating a new child context.
   *
   * This is an alias for `Context::create(parentContext`
   *
   * @return A new child context
   */
  std::unique_ptr<ChildContext> Fork();

  /**
   * Joins the provided child context into the current context.
   * The provided child context must be a direct child of the current context (for example, created by `fork`)
   *
   * All the variables set of the provided child context will be merged with the one of the current context.
   * The symbols table won't be merged.
   * The provided source context will be deleted.
   *
   * @param child_context The child context to join into this context.
   */
  void Join(std::unique_ptr<ChildContext> child_context);

 protected:
  /**
   * Symbol table
   */
  SymbolTable symbols_;

  /**
   * Shadowed and anonymous variables.
   */
  std::set<std::shared_ptr<const Variable>> variables_;
};

class RootContext final : public Context {
 public:
  static std::unique_ptr<RootContext> Create();
  static std::unique_ptr<RootContext> Create(
    SymbolTable symbols,
    std::set<std::shared_ptr<const Variable>> variables);

  RootContext();
  RootContext(
    SymbolTable symbols,
    std::set<std::shared_ptr<const Variable>> variables);

  ~RootContext();

  std::shared_ptr<const DataType> ResolveDataType(
    const std::string &name) const;
  std::shared_ptr<FunctionSymbol> ResolveFunction(
    const std::string &name) const;
  std::shared_ptr<const Variable> ResolveVariable(
    const std::string &name) const;
};

class ChildContext final : public Context {
 public:
  static std::unique_ptr<ChildContext> Create(Context &parentContext);
  static std::unique_ptr<ChildContext> Create(
    Context &parent_context,
    SymbolTable symbols,
    std::set<std::shared_ptr<const Variable>> variables);

  ChildContext(Context &parentContext);
  ChildContext(
    Context &parentContext,
    SymbolTable symbols,
    std::set<std::shared_ptr<const Variable>> variables);

  ~ChildContext();

  std::shared_ptr<const DataType> ResolveDataType(
    const std::string &name) const;
  std::shared_ptr<FunctionSymbol> ResolveFunction(
    const std::string &name) const;
  std::shared_ptr<const Variable> ResolveVariable(
    const std::string &name) const;

 protected:
  Context &parent_context_;
};
}  // namespace ir
}  // namespace comp
