#include <comp/as/arch/x64/build_asm.h>

#include <comp/as/arch/x64/stddef.h>
#include <comp/exceptions.h>

namespace comp {
namespace as {
namespace arch {
namespace x64 {

static const std::shared_ptr<ast::Mnemonic>
  LEAVEQ = ast::Mnemonic::Create("leaveq"),
  MOVQ = ast::Mnemonic::Create("movq"),
  PUSHQ = ast::Mnemonic::Create("pushq"),
  RETQ = ast::Mnemonic::Create("retq"),
  SUBQ = ast::Mnemonic::Create("subq");

static const std::shared_ptr<ast::RegisterOperand>
  RBP = ast::RegisterOperand::Create("rbp"),
  RSP = ast::RegisterOperand::Create("rsp");

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

  // Calculate the stack size
  int64_t stack_size = 0;
  for (auto variable : node->GetLocalVariables()) {
    stack_size += GetDataTypeSize(variable->GetDataType());
  }

  // Prologue
  body.insert(body.end(), {
    ast::GlobalDirective::Create(symbol),
    ast::EmptyStatement::Create({symbol}),
    ast::Instruction::Create(PUSHQ, {RBP}),
    ast::Instruction::Create(MOVQ, {RSP, RBP})
  });
  if (stack_size > 0) {
    body.push_back(
      ast::Instruction::Create(
        SUBQ,
        {ast::ImmediateOperand::Create(stack_size), RBP}));
  }

  // Epilogue
  body.insert(body.end(), {
    ast::Instruction::Create(LEAVEQ),
    ast::Instruction::Create(RETQ)
  });
}
}  // namespace x64
}  // namespace arch
}  // namespace as
}  // namespace comp
