#include <comp/ir/program_symbol.h>
#include <set>

namespace comp {
namespace ir {
ProgramSymbol::~ProgramSymbol() {
}

DataObjectSymbol::DataObjectSymbol() {
  throw std::string("Not implemented");
}

std::unique_ptr<FunctionSymbol> FunctionSymbol::Create(
  std::vector<std::shared_ptr<const Variable>> parameters,
  std::shared_ptr<const DataType> return_type,
  std::shared_ptr<BasicBlock> body
) {
  return std::unique_ptr<FunctionSymbol>(
    new FunctionSymbol(parameters, return_type, body));
}

FunctionSymbol::FunctionSymbol(
  std::vector<std::shared_ptr<const Variable>> parameters,
  std::shared_ptr<const DataType> return_type,
  std::shared_ptr<BasicBlock> body
) : parameters_(parameters), return_type_(return_type), body_(body) {
}

FunctionSymbol::~FunctionSymbol() {
}

std::shared_ptr<BasicBlock> FunctionSymbol::GetBody() const {
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

void FunctionSymbol::SetBody(std::shared_ptr<BasicBlock> body) {
  body_ = body;
}

void FunctionSymbol::SetLocalVariables(
  std::set<std::shared_ptr<const Variable>> local_variables) {
  local_variables_ = local_variables;
}
}  // namespace ir
}  // namespace comp

