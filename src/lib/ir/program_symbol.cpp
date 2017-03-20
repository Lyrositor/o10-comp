#include <comp/ir/program_symbol.h>

namespace comp {
namespace ir {
ProgramSymbol::~ProgramSymbol() {
}

DataObjectSymbol::DataObjectSymbol() {
  throw std::string("Not implemented");
}

std::unique_ptr<FunctionSymbol> FunctionSymbol::Create(
  std::vector<std::shared_ptr<const Parameter>> parameters,
  std::shared_ptr<const DataType> return_type,
  std::shared_ptr<BasicBlock> body
) {
  return std::unique_ptr<FunctionSymbol>(
    new FunctionSymbol(parameters, return_type, body));
}

FunctionSymbol::FunctionSymbol(
  std::vector<std::shared_ptr<const Parameter>> parameters,
  std::shared_ptr<const DataType> return_type,
  std::shared_ptr<BasicBlock> body
) : parameters_(parameters), return_type_(return_type), body_(body) {
}

FunctionSymbol::~FunctionSymbol() {
}

std::shared_ptr<const DataType> FunctionSymbol::GetReturnType() const {
  return return_type_;
}

void FunctionSymbol::SetBody(std::shared_ptr<BasicBlock> body) {
  body_ = body;
}
}  // namespace ir
}  // namespace comp

