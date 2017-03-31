#include <comp/as/backend/x64/build_asm.h>

#include <memory>

#include <comp/exceptions.h>
#include <comp/ir/program.h>

namespace comp {
namespace as {
namespace backend {
namespace x64 {
std::shared_ptr<ast::Program> BuildProgram(const ir::Program &node) {
  std::vector<std::shared_ptr<ast::Statement>> body;

  body.push_back(ast::TextDirective::Create());

  for (auto ir_symbol : node.GetSymbols()) {
    switch (ir_symbol->GetType()) {
      case ir::ProgramSymbol::Type::DataObject: {
        throw Exception("Not implemented yet");
      }
      case ir::ProgramSymbol::Type::Function: {
        BuildFunction(
          std::static_pointer_cast<const ir::FunctionSymbol>(ir_symbol),
          body);
        break;
      }
    }
  }

  std::shared_ptr<ast::Program> program = ast::Program::Create(body);
  return program;
}

void BuildFunction(
  std::shared_ptr<const ir::FunctionSymbol> node,
  std::vector<std::shared_ptr<ast::Statement>> &body
) {
  std::shared_ptr<ast::GlobalSymbol> symbol = ast::GlobalSymbol::Create(
    node->GetName());
  body.push_back(ast::GlobalDirective::Create(symbol));
  body.push_back(ast::EmptyStatement::Create({symbol}));
  body.push_back(ast::Instruction::Create(ast::Mnemonic::Create("enterq"), {ast::ImmediateOperand::Create(0), ast::ImmediateOperand::Create(0)}));
  body.push_back(ast::Instruction::Create(ast::Mnemonic::Create("leaveq"), {}));
  body.push_back(ast::Instruction::Create(ast::Mnemonic::Create("retq"), {}));
}
}  // namespace x64
}  // namespace backend
}  // namespace as
}  // namespace comp
