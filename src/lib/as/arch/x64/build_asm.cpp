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
  R8 = ast::RegisterOperand::Create("r8"),
  R9 = ast::RegisterOperand::Create("r9"),
  R10 = ast::RegisterOperand::Create("r9"),
  R11 = ast::RegisterOperand::Create("r11"),
  R12 = ast::RegisterOperand::Create("r12"),
  R13 = ast::RegisterOperand::Create("r13"),
  R14 = ast::RegisterOperand::Create("r14"),
  R15 = ast::RegisterOperand::Create("r15"),

  RAX = ast::RegisterOperand::Create("rax"),
  RBX = ast::RegisterOperand::Create("rbx"),
  RCX = ast::RegisterOperand::Create("rcx"),
  RDX = ast::RegisterOperand::Create("rdx"),

  RBP = ast::RegisterOperand::Create("rbp"),
  RSP = ast::RegisterOperand::Create("rsp"),

  RDI = ast::RegisterOperand::Create("rdi"),
  RSI = ast::RegisterOperand::Create("rdi");

static const std::vector<std::shared_ptr<ast::RegisterOperand>>
  kParameterRegisters = {RDI, RSI, RDX, RCX, R8, R9};

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

  // Store the memory references of the parameters
  // The six first parameters are stored in the registers specified by
  // kParameterRegisters (in left-to-right order).
  // All subsequent parameters are pushed on to the stack before the return
  // address and the old RBP (in right-to-left order)
  VariablesTable variables_table;
  auto params = node->GetParameters();
  for (size_t idx = 0; idx < kParameterRegisters.size() && idx < params.size();
       idx++) {
    variables_table.Register(
      params[idx],
      ast::MemoryReference::Create(kParameterRegisters[idx]));
  }
  size_t param_stack_size = 0;
  for (size_t idx = params.size()-1; idx > kParameterRegisters.size(); idx--) {
    variables_table.Register(
      params[idx],
      ast::MemoryReference::Create(
        RBP,
        ast::ImmediateOperand::Create(kRegisterSize*2 + param_stack_size)));
    param_stack_size += GetDataTypeSize(params[idx]->GetDataType());
  }

  // Store the memory references of the other local variables on the stack
  int64_t stack_size = 0;
  for (auto variable : node->GetLocalVariables()) {
    if (variables_table.Contains(variable)) {  // Don't count the parameters
      continue;
    }
    stack_size += GetDataTypeSize(variable->GetDataType());
    variables_table.Register(variable, ast::MemoryReference::Create(
      RBP,
      ast::ImmediateOperand::Create(-stack_size)));
  }

  // Prolog
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

  // Generate the function body
  BuildBasicBlock(node->GetBody()->GetSource(), body, variables_table);

  // Epilog
  body.insert(body.end(), {
    ast::Instruction::Create(LEAVEQ),
    ast::Instruction::Create(RETQ)
  });
}

void BuildBasicBlock(
  std::shared_ptr<ir::BasicBlock> block,
  const std::vector<std::shared_ptr<ast::Statement>> &body,
  VariablesTable &variables_table
) {

}
}  // namespace x64
}  // namespace arch
}  // namespace as
}  // namespace comp
