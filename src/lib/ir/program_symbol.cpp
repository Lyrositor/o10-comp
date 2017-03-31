#include <comp/ir/program_symbol.h>

namespace comp {
namespace ir {
ProgramSymbol::ProgramSymbol(ProgramSymbol::Type type) : type_(type) {
}

ProgramSymbol::~ProgramSymbol() {
}

ProgramSymbol::Type ProgramSymbol::GetType() const {
  return type_;
}

DataObjectSymbol::DataObjectSymbol() : ProgramSymbol(Type::DataObject) {
  throw std::string("Not implemented");
}

std::unique_ptr<FunctionSymbol> FunctionSymbol::Create(
  const std::string &name,
  std::vector<std::shared_ptr<const Variable>> parameters,
  std::shared_ptr<const DataType> return_type,
  std::shared_ptr<ControlFlowGraph> body
) {
  return std::unique_ptr<FunctionSymbol>(
    new FunctionSymbol(name, parameters, return_type, body));
}

FunctionSymbol::FunctionSymbol(
  const std::string &name,
  std::vector<std::shared_ptr<const Variable>> parameters,
  std::shared_ptr<const DataType> return_type,
  std::shared_ptr<ControlFlowGraph> body
) :
  ProgramSymbol(Type::Function),
  name_(name),
  parameters_(parameters),
  return_type_(return_type),
  body_(body) {
}

FunctionSymbol::~FunctionSymbol() {
}

std::string FunctionSymbol::GetName() const {
  return name_;
}

std::shared_ptr<ControlFlowGraph> FunctionSymbol::GetBody() const {
  return body_;
}

std::vector<std::shared_ptr<const Variable>> FunctionSymbol::GetParameters()
const {
  return parameters_;
}

std::shared_ptr<const DataType> FunctionSymbol::GetReturnType() const {
  return return_type_;
}

std::set<std::shared_ptr<const Variable>> FunctionSymbol::GetLocalVariables()
const {
  return local_variables_;
}

void FunctionSymbol::SetBody(std::shared_ptr<ControlFlowGraph> body) {
  body_ = body;
}

void FunctionSymbol::SetLocalVariables(
  std::set<std::shared_ptr<const Variable>> local_variables) {
  local_variables_ = local_variables;
}
}  // namespace ir
}  // namespace comp

