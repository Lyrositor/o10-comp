#include <comp/ir/context.h>

#include <cstddef>

#include <comp/utils.h>

namespace comp {
namespace ir {
// Context
Context::Context() :
  symbols_(std::move(SymbolTable())),
  variables_(std::move(std::set<std::shared_ptr<const Variable>>())) {
}

Context::Context(
  SymbolTable symbols,
  std::set<std::shared_ptr<const Variable>> variables
) : symbols_(std::move(symbols)), variables_(std::move(variables)) {
}

Context::~Context() {
}

void Context::RegisterDataType(
  const std::string name, std::shared_ptr<const DataType> data_type
) {
  symbols_.data_types[name] = data_type;
}

void Context::RegisterVariable(
  const std::string name, std::shared_ptr<const Variable> variable
) {
  symbols_.variables[name] = variable;
  variables_.insert(variable);
}

void Context::RegisterFunction(
  const std::string name, std::shared_ptr<FunctionSymbol> function
) {
  symbols_.functions[name] = function;
}

std::shared_ptr<const Variable> Context::CreateVariable(
  std::shared_ptr<const DataType> data_type,
  const std::shared_ptr<const ast::Node> node
) {
  std::shared_ptr<const Variable> result = Variable::Create(
    data_type, node);
  variables_.insert(result);
  return result;
}

std::set<std::shared_ptr<const Variable>> Context::GetVariables() const {
  return std::set<std::shared_ptr<const Variable>>(variables_);
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
  SymbolTable symbols,
  std::set<std::shared_ptr<const Variable>> variables
) {
  return std::unique_ptr<RootContext>(
    new RootContext(std::move(symbols), std::move(variables))
  );
}

RootContext::RootContext() : Context() {
}

RootContext::RootContext(
  SymbolTable symbols,
  std::set<std::shared_ptr<const Variable>> variables
) : Context(std::move(symbols), std::move(variables)) {
}

RootContext::~RootContext() {
}

std::shared_ptr<const DataType> RootContext::ResolveDataType(
  const std::string &name
) const {
  auto it = symbols_.data_types.find(name);
  if (it != symbols_.data_types.end()) {
    return it->second;
  } else {
    throw std::runtime_error(std::string("Unknown data_type"));
  }
}

std::shared_ptr<const Variable> RootContext::ResolveVariable(
  const std::string &name
) const {
  auto it = symbols_.variables.find(name);
  if (it != symbols_.variables.end()) {
    return it->second;
  } else {
    throw std::runtime_error(std::string("Unknown variable"));
  }
}

std::shared_ptr<FunctionSymbol> RootContext::ResolveFunction(
  const std::string &name
) const {
  auto it = symbols_.functions.find(name);
  if (it != symbols_.functions.end()) {
    return it->second;
  } else {
    throw std::runtime_error(std::string("Unknown function"));
  }
}

bool RootContext::HasVariable(std::string name, bool check_parents) {
  UNUSED(check_parents);
  auto it = symbols_.variables.find(name);
  return it != symbols_.variables.end();
}

bool RootContext::HasDataType(std::string name, bool check_parents) {
  UNUSED(check_parents);
  auto it = symbols_.data_types.find(name);
  return it != symbols_.data_types.end();
}

bool RootContext::HasFunction(std::string name, bool check_parents) {
  UNUSED(check_parents);
  auto it = symbols_.functions.find(name);
  return it != symbols_.functions.end();
}

// ChildContext
std::unique_ptr<ChildContext> ChildContext::Create(Context &parentContext) {
  return std::unique_ptr<ChildContext>(new ChildContext(parentContext));
}

std::unique_ptr<ChildContext> ChildContext::Create(
  Context &parent_context,
  SymbolTable symbols,
  std::set<std::shared_ptr<const Variable>> variables
) {
  return std::unique_ptr<ChildContext>(
    new ChildContext(
      parent_context,
      std::move(symbols),
      std::move(variables)
    )
  );
}

ChildContext::ChildContext(Context &parentContext)
  : Context(), parent_context_(parentContext) {
}

ChildContext::ChildContext(
  Context &parentContext,
  SymbolTable symbols,
  std::set<std::shared_ptr<const Variable>> variables
) :
  Context(std::move(symbols), std::move(variables)),
  parent_context_(parentContext) {
}

ChildContext::~ChildContext() {
}

std::shared_ptr<const DataType> ChildContext::ResolveDataType(
  const std::string &name
) const {
  auto it = symbols_.data_types.find(name);
  if (it != symbols_.data_types.end()) {
    return it->second;
  } else {
    return parent_context_.ResolveDataType(name);
  }
}

std::shared_ptr<const Variable> ChildContext::ResolveVariable(
  const std::string &name
) const {
  auto it = symbols_.variables.find(name);
  if (it != symbols_.variables.end()) {
    return it->second;
  } else {
    return parent_context_.ResolveVariable(name);
  }
}

std::shared_ptr<FunctionSymbol> ChildContext::ResolveFunction(
  const std::string &name
) const {
  auto it = symbols_.functions.find(name);
  if (it != symbols_.functions.end()) {
    return it->second;
  } else {
    return parent_context_.ResolveFunction(name);
  }
}

bool ChildContext::HasVariable(std::string name, bool check_parents) {
  if (symbols_.variables.find(name) != symbols_.variables.end()) {
    return true;
  } else if(check_parents) {
    return parent_context_.HasVariable(name, true);
  } else {
    return false;
  }
}

bool ChildContext::HasDataType(std::string name, bool check_parents) {
  if (symbols_.data_types.find(name) != symbols_.data_types.end()) {
    return true;
  } else if(check_parents) {
    return parent_context_.HasDataType(name, true);
  } else {
    return false;
  }
}

bool ChildContext::HasFunction(std::string name, bool check_parents) {
  if (symbols_.functions.find(name) != symbols_.functions.end()) {
    return true;
  } else if(check_parents) {
    return parent_context_.HasFunction(name, true);
  } else {
    return false;
  }
}
}  // namespace ir
}  // namespace comp
