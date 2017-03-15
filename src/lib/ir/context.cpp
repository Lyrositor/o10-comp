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
  data_types_table_(std::move(std::map<std::string,
                                      std::shared_ptr<DataType>>())),
  variables_table_(std::move(std::map<std::string,
                                     std::shared_ptr<Variable>>())),
  functions_table_(std::move(std::map<std::string,
                                     std::shared_ptr<Function>>())),
  variables_(std::move(std::set<std::shared_ptr<Variable>>())) {
}

Context::Context(
  std::map<std::string, std::shared_ptr<DataType>> data_types_table,
  std::map<std::string, std::shared_ptr<Variable>> variables_table,
  std::map<std::string, std::shared_ptr<Function>> functions_table,
  std::set<std::shared_ptr<Variable>> variables
) :
  data_types_table_(std::move(data_types_table)),
  variables_table_(std::move(variables_table)),
  functions_table_(std::move(functions_table)),
  variables_(std::move(variables)) {
}

Context::~Context() {
}

void Context::RegisterDataType(const std::string name,
                               std::shared_ptr<DataType> data_type) {
  data_types_table_[name] = data_type;
}

void Context::RegisterVariable(const std::string name,
                               std::shared_ptr<Variable> variable) {
  variables_table_[name] = variable;
  variables_.insert(variable);
}

void Context::RegisterFunction(const std::string name,
                               std::shared_ptr<Function> function) {
  functions_table_[name] = function;
}

std::shared_ptr<Variable> Context::CreateVariable(std::shared_ptr<const DataType> data_type) {
  std::shared_ptr<Variable> result = Variable::Create(data_type);
  variables_.insert(result);
  return result;
}

std::set<std::shared_ptr<Variable>> Context::GetVariables() const {
  return std::set<std::shared_ptr<Variable>>(variables_);
}

std::unique_ptr<ChildContext> Context::Fork() {
  return std::unique_ptr<ChildContext>(new ChildContext(*this));
}

void Context::Join(std::unique_ptr<ChildContext> child_context) {
  /*if (&child_context->GetParentContext() != this) {
    throw std::runtime_error("Not a child context");
  }*/
  variables_.insert(
    child_context->variables_.begin(),
    child_context->variables_.end()
  );
}

// RootContext
std::unique_ptr<RootContext> RootContext::Create() {
  return std::unique_ptr<RootContext>(new RootContext());
}

std::unique_ptr<RootContext> RootContext::Create(
  std::map<std::string, std::shared_ptr<DataType>> data_types_table,
  std::map<std::string, std::shared_ptr<Variable>> variables_table,
  std::map<std::string, std::shared_ptr<Function>> functions_table,
  std::set<std::shared_ptr<Variable>> variables
) {
  return std::unique_ptr<RootContext>(
    new RootContext(
      std::move(data_types_table),
      std::move(variables_table),
      std::move(functions_table),
      std::move(variables)
    )
  );
}

RootContext::RootContext() : Context() {
}

RootContext::RootContext(
  std::map<std::string, std::shared_ptr<DataType>> data_types_table,
  std::map<std::string, std::shared_ptr<Variable>> variables_table,
  std::map<std::string, std::shared_ptr<Function>> functions_table,
  std::set<std::shared_ptr<Variable>> variables
) :
  Context(std::move(data_types_table),
          std::move(variables_table),
          std::move(functions_table),
          std::move(variables)) {
}

RootContext::~RootContext() {
}

std::shared_ptr<DataType> RootContext::ResolveDataType(const std::string &name) const {
  auto it = data_types_table_.find(name);
  if (it != data_types_table_.end()) {
    return it->second;
  } else {
    throw std::runtime_error(std::string("Unknown dataType"));
  }
}

std::shared_ptr<Variable> RootContext::ResolveVariable(const std::string &name) const {
  auto it = variables_table_.find(name);
  if (it != variables_table_.end()) {
    return it->second;
  } else {
    throw std::runtime_error(std::string("Unknown variable"));
  }
}

std::shared_ptr<Function> RootContext::ResolveFunction(const std::string &name) const {
  auto it = functions_table_.find(name);
  if (it != functions_table_.end()) {
    return it->second;
  } else {
    throw std::runtime_error(std::string("Unknown function"));
  }
}

// ChildContext
std::unique_ptr<ChildContext> ChildContext::Create(Context &parentContext) {
  return std::unique_ptr<ChildContext>(new ChildContext(parentContext));
}

std::unique_ptr<ChildContext> ChildContext::Create(
  Context &parent_context,
  std::map<std::string, std::shared_ptr<DataType>> data_types_table,
  std::map<std::string, std::shared_ptr<Variable>> variables_table,
  std::map<std::string, std::shared_ptr<Function>> functions_table,
  std::set<std::shared_ptr<Variable>> variables
) {
  return std::unique_ptr<ChildContext>(
    new ChildContext(
      parent_context,
      std::move(data_types_table),
      std::move(variables_table),
      std::move(functions_table),
      std::move(variables)
    )
  );
}

ChildContext::ChildContext(Context &parentContext)
  : Context(), parent_context_(parentContext) {
}

ChildContext::ChildContext(
  Context &parentContext,
  std::map<std::string, std::shared_ptr<DataType>> data_types_table,
  std::map<std::string, std::shared_ptr<Variable>> variables_table,
  std::map<std::string, std::shared_ptr<Function>> functions_table,
  std::set<std::shared_ptr<Variable>> variables
) :
  Context(std::move(data_types_table),
          std::move(variables_table),
          std::move(functions_table),
          std::move(variables)),
  parent_context_(parentContext) {
}

ChildContext::~ChildContext() {
}

std::shared_ptr<DataType> ChildContext::ResolveDataType(const std::string &name) const {
  auto it = data_types_table_.find(name);
  if (it != data_types_table_.end()) {
    return it->second;
  } else {
    return parent_context_.ResolveDataType(name);
  }
}

std::shared_ptr<Variable> ChildContext::ResolveVariable(const std::string &name) const {
  auto it = variables_table_.find(name);
  if (it != variables_table_.end()) {
    return it->second;
  } else {
    return parent_context_.ResolveVariable(name);
  }
}

std::shared_ptr<Function> ChildContext::ResolveFunction(const std::string &name) const {
  auto it = functions_table_.find(name);
  if (it != functions_table_.end()) {
    return it->second;
  } else {
    return parent_context_.ResolveFunction(name);
  }
}
}
}
