#include <comp/ir/context.h>
#include <comp/ir/data_type.h>
#include <comp/ir/function.h>
#include <comp/ir/variable.h>
#include <cstddef>
#include <memory>

namespace comp {
namespace ir {
Context::Context(std::shared_ptr<Context> parentContext) :
  parentContext(parentContext),
  dataTypesTable(std::map<std::string, std::shared_ptr<DataType>>()),
  variablesTable(std::map<std::string, std::shared_ptr<Variable>>()),
  functionsTable(std::map<std::string, std::shared_ptr<Function>>()),
  variables(std::set<std::shared_ptr<Variable>>()) {
}

Context::Context(
  std::shared_ptr<Context> parentContext,
  std::map<std::string, std::shared_ptr<DataType>> dataTypesTable,
  std::map<std::string, std::shared_ptr<Variable>> variablesTable,
  std::map<std::string, std::shared_ptr<Function>> functionsTable,
  std::set<std::shared_ptr<Variable>> variables
) :
  parentContext(parentContext),
  dataTypesTable(dataTypesTable),
  variablesTable(variablesTable),
  functionsTable(functionsTable),
  variables(variables)
{
}

std::shared_ptr<Variable> Context::createVariable(std::shared_ptr<DataType> dataType) {
  std::shared_ptr<Variable> result = Variable::create(dataType);
  this->variables.insert(result);
  return result;
}

void Context::registerDataType(std::string name, std::shared_ptr<DataType> dataType) {
  this->dataTypesTable.emplace(name, dataType);
}

void Context::registerVariable(std::string name, std::shared_ptr<Variable> variable) {
  this->variablesTable.emplace(name, variable);
  this->variables.insert(variable);
}

void Context::registerFunction(std::string name, std::shared_ptr<Function> function) {
  this->functionsTable.emplace(name, function);
}

std::shared_ptr<DataType> Context::resolveDataType(std::string &name) const {
  auto it = this->dataTypesTable.find(name);
  if (it != this->dataTypesTable.end()) {
    return it->second;
  } else if(this->parentContext != nullptr) {
    return this->parentContext->resolveDataType(name);
  } else {
    throw std::runtime_error(std::string("Unkown dataType"));
  }
}

std::shared_ptr<Variable> Context::resolveVariable(std::string &name) const {
  auto it = this->variablesTable.find(name);
  if (it != this->variablesTable.end()) {
    return it->second;
  } else if(this->parentContext != nullptr) {
    return this->parentContext->resolveVariable(name);
  } else {
    throw std::runtime_error(std::string("Unkown variable"));
  }
}

std::shared_ptr<Function> Context::resolveFunction(std::string &name) const {
  auto it = this->functionsTable.find(name);
  if (it != this->functionsTable.end()) {
    return it->second;
  } else if(this->parentContext != nullptr) {
    return this->parentContext->resolveFunction(name);
  } else {
    throw std::runtime_error(std::string("Unkown function"));
  }
}

Context::~Context() {}
}
}
