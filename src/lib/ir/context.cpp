#include <comp/ir/context.h>
#include <comp/ir/data_type.h>
#include <comp/ir/function.h>
#include <comp/ir/variable.h>
#include <cstddef>
#include <memory>

namespace comp {
namespace ir {
// Context
Context::Context() :
  dataTypesTable(std::move(std::map<std::string, std::shared_ptr<DataType>>())),
  variablesTable(std::move(std::map<std::string, std::shared_ptr<Variable>>())),
  functionsTable(std::move(std::map<std::string, std::shared_ptr<Function>>())),
  variables(std::move(std::set<std::shared_ptr<Variable>>())) {
}

Context::Context(
  std::map<std::string, std::shared_ptr<DataType>> dataTypesTable,
  std::map<std::string, std::shared_ptr<Variable>> variablesTable,
  std::map<std::string, std::shared_ptr<Function>> functionsTable,
  std::set<std::shared_ptr<Variable>> variables
) :
  dataTypesTable(std::move(dataTypesTable)),
  variablesTable(std::move(variablesTable)),
  functionsTable(std::move(functionsTable)),
  variables(std::move(variables)) {
}

void Context::registerDataType(std::string name, std::shared_ptr<DataType> dataType) {
  this->dataTypesTable[name] = dataType;
}

void Context::registerVariable(std::string name, std::shared_ptr<Variable> variable) {
  this->variablesTable[name] = variable;
  this->variables.insert(variable);
}

void Context::registerFunction(std::string name, std::shared_ptr<Function> function) {
  this->functionsTable[name] = function;
}

std::shared_ptr<Variable> Context::createVariable(std::shared_ptr<const DataType> dataType) {
  std::shared_ptr<Variable> result = Variable::create(dataType);
  this->variables.insert(result);
  return result;
}

std::set<std::shared_ptr<Variable>> Context::getVariables() const {
  return std::set<std::shared_ptr<Variable>>(this->variables);
}

std::unique_ptr<ChildContext> Context::fork() {
  return std::unique_ptr<ChildContext>(new ChildContext(*this));
}

void Context::join(std::unique_ptr<ChildContext> childContext) {
//  if (childContext->parentContext.get() != this) {
//    throw std::runtime_error("Not a child context");
//  }
  this->variables.insert(childContext->variables.begin(), childContext->variables.end());
}

Context::~Context() {
}

// RootContext
std::unique_ptr<RootContext> RootContext::create() {
  return std::unique_ptr<RootContext>(new RootContext());
}

std::unique_ptr<RootContext> RootContext::create(
  std::map<std::string, std::shared_ptr<DataType>> dataTypesTable,
  std::map<std::string, std::shared_ptr<Variable>> variablesTable,
  std::map<std::string, std::shared_ptr<Function>> functionsTable,
  std::set<std::shared_ptr<Variable>> variables
) {
  return std::unique_ptr<RootContext>(
    new RootContext(
      std::move(dataTypesTable),
      std::move(variablesTable),
      std::move(functionsTable),
      std::move(variables)
    )
  );
}

RootContext::RootContext() : Context() {
}

RootContext::RootContext(
  std::map<std::string, std::shared_ptr<DataType>> dataTypesTable,
  std::map<std::string, std::shared_ptr<Variable>> variablesTable,
  std::map<std::string, std::shared_ptr<Function>> functionsTable,
  std::set<std::shared_ptr<Variable>> variables
) :
  Context(std::move(dataTypesTable), std::move(variablesTable), std::move(functionsTable), std::move(variables)) {
}

std::shared_ptr<DataType> RootContext::resolveDataType(const std::string &name) const {
  auto it = this->dataTypesTable.find(name);
  if (it != this->dataTypesTable.end()) {
    return it->second;
  } else {
    throw std::runtime_error(std::string("Unkown dataType"));
  }
}

std::shared_ptr<Variable> RootContext::resolveVariable(const std::string &name) const {
  auto it = this->variablesTable.find(name);
  if (it != this->variablesTable.end()) {
    return it->second;
  } else {
    throw std::runtime_error(std::string("Unkown variable"));
  }
}

std::shared_ptr<Function> RootContext::resolveFunction(const std::string &name) const {
  auto it = this->functionsTable.find(name);
  if (it != this->functionsTable.end()) {
    return it->second;
  } else {
    throw std::runtime_error(std::string("Unkown function"));
  }
}

RootContext::~RootContext() {
}

// ChildContext
std::unique_ptr<ChildContext> ChildContext::create(Context &parentContext) {
  return std::unique_ptr<ChildContext>(new ChildContext(parentContext));
}

std::unique_ptr<ChildContext> ChildContext::create(
  Context &parentContext,
  std::map<std::string, std::shared_ptr<DataType>> dataTypesTable,
  std::map<std::string, std::shared_ptr<Variable>> variablesTable,
  std::map<std::string, std::shared_ptr<Function>> functionsTable,
  std::set<std::shared_ptr<Variable>> variables
) {
  return std::unique_ptr<ChildContext>(
    new ChildContext(
      parentContext,
      std::move(dataTypesTable),
      std::move(variablesTable),
      std::move(functionsTable),
      std::move(variables)
    )
  );
}

ChildContext::ChildContext(Context &parentContext) : Context(), parentContext(parentContext) {
}

ChildContext::ChildContext(
  Context &parentContext,
  std::map<std::string, std::shared_ptr<DataType>> dataTypesTable,
  std::map<std::string, std::shared_ptr<Variable>> variablesTable,
  std::map<std::string, std::shared_ptr<Function>> functionsTable,
  std::set<std::shared_ptr<Variable>> variables
) :
  Context(std::move(dataTypesTable), std::move(variablesTable), std::move(functionsTable), std::move(variables)),
  parentContext(parentContext) {
}

std::shared_ptr<DataType> ChildContext::resolveDataType(const std::string &name) const {
  auto it = this->dataTypesTable.find(name);
  if (it != this->dataTypesTable.end()) {
    return it->second;
  } else {
    return this->parentContext.resolveDataType(name);
  }
}

std::shared_ptr<Variable> ChildContext::resolveVariable(const std::string &name) const {
  auto it = this->variablesTable.find(name);
  if (it != this->variablesTable.end()) {
    return it->second;
  } else {
    return this->parentContext.resolveVariable(name);
  }
}

std::shared_ptr<Function> ChildContext::resolveFunction(const std::string &name) const {
  auto it = this->functionsTable.find(name);
  if (it != this->functionsTable.end()) {
    return it->second;
  } else {
    return this->parentContext.resolveFunction(name);
  }
}

ChildContext::~ChildContext() {
}
}
}
