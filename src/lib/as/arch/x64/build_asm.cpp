#include <comp/as/arch/x64/build_asm.h>

#include <comp/as/arch/x64/stddef.h>
#include <comp/ir/builtins.h>
#include <comp/utils.h>
#include <comp/exceptions.h>
#include <queue>

namespace comp {
namespace as {
namespace arch {
namespace x64 {
static const std::shared_ptr<ast::Mnemonic>
  ADDQ = ast::Mnemonic::Create("addq"),
  CALL = ast::Mnemonic::Create("call"),
  LEAVEQ = ast::Mnemonic::Create("leaveq"),
  MOVQ = ast::Mnemonic::Create("movq"),
  NOP = ast::Mnemonic::Create("nop"),
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
  RSI = ast::RegisterOperand::Create("rsi");

static const std::vector<std::shared_ptr<ast::RegisterOperand>>
#ifdef WIN32
  kParameterRegisters = {RCX, RDX, R8, R9};
#else
  kParameterRegisters = {RDI, RSI, RDX, RCX, R8, R9};
#endif

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
  VariablesTable variables_table;
  auto params = node->GetParameters();

  // Store the memory references of the parameters
  // The first few parameters are passed through the registers specified by
  // kParameterRegisters (in left-to-right order).
  // All subsequent parameters are pushed on to the stack before the return
  // address and the old RBP (in right-to-left order).
  int64_t param_stack_size = 0;
  std::vector<std::shared_ptr<ast::Instruction>> param_copies;
  for (size_t idx = 0; idx < params.size(); idx++) {
    std::shared_ptr<ast::MemoryReference> address;

    // Copy the parameter's value if it came from a register
    if (idx < kParameterRegisters.size()) {
      address = ast::MemoryReference::Create(
        RBP,
        ast::BigIntegerLiteral::Create(-kRegisterSize*(idx + 1)));
      param_copies.push_back(ast::Instruction::Create(
        MOVQ,
        {kParameterRegisters[idx], address}));
    } else {
      address = ast::MemoryReference::Create(
        RBP,
        ast::BigIntegerLiteral::Create(kRegisterSize*2 + param_stack_size));
      //param_stack_size += GetDataTypeSize(params[idx]->GetDataType()); TODO(Lyrositor) Use the right data type size
      param_stack_size += kRegisterSize;
    }
    variables_table.Register(params[idx], address);
  }

  // Store the memory references of the other local variables on the stack
  // The bottom of the stack (highest addresses) are reserved for the register
  // parameters, even if there are none to be copied.
  int64_t stack_size = kRegisterSize * kParameterRegisters.size();
  for (auto variable : node->GetLocalVariables()) {
    if (variables_table.Contains(variable)) {  // Don't count the parameters
      continue;
    }
    //stack_size += GetDataTypeSize(variable->GetDataType());  TODO(Lyrositor) Use the right data type size
    stack_size += kRegisterSize;
    variables_table.Register(variable, ast::MemoryReference::Create(
      RBP,
      ast::BigIntegerLiteral::Create(-stack_size)));
  }

  // Prolog
  std::shared_ptr<ast::GlobalSymbol> symbol = ast::GlobalSymbol::Create(
    node->GetName());
  body.insert(body.end(), {
    ast::GlobalDirective::Create(symbol),
    ast::EmptyStatement::Create({symbol}),
    ast::Instruction::Create(PUSHQ, {RBP}),
    ast::Instruction::Create(MOVQ, {RSP, RBP})
  });
  body.push_back(
    ast::Instruction::Create(
      SUBQ,
      {ast::ImmediateOperand::Create(stack_size), RSP}));

  // Copy the register parameters
  for (auto instruction : param_copies) {
    body.push_back(instruction);
  }

  // Generate the function body
  BuildBasicBlock(node->GetBody()->GetSource(), body, variables_table);

  // Epilog
  // TODO(Lyrositor) If there are multiple blocks, add a return label here
  body.insert(body.end(), {
    ast::Instruction::Create(LEAVEQ),
    ast::Instruction::Create(RETQ)
  });

  // Generate every subsequent block
  std::set<std::shared_ptr<ir::BasicBlock>>
    remaining_blocks = node->GetBody()->GetBasicBlocks();
  remaining_blocks.erase(node->GetBody()->GetSource());
  for (auto block : node->GetBody()->GetBasicBlocks()) {
    // TODO(Lyrositor) Generate eve
    remaining_blocks.erase(block);
  }
}

void BuildBasicBlock(
  std::shared_ptr<ir::BasicBlock> block,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  VariablesTable &variables_table
) {
  for (auto op : block->GetOps()) {
    BuildOp(op, body, variables_table);
  }
}

void BuildOp(
  std::shared_ptr<ir::Op> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  VariablesTable &variables_table
) {
  switch (op->op_type) {
    case ir::Op::Type::BinOp:
      BuildBinOp(
        std::static_pointer_cast<ir::BinOp>(op),
        body,
        variables_table);
      break;
    case ir::Op::Type::CallOp:
      BuildCallOp(
        std::static_pointer_cast<ir::CallOp>(op),
        body,
        variables_table);
      break;
    case ir::Op::Type::CopyOp:
      BuildCopyOp(
        std::static_pointer_cast<ir::CopyOp>(op),
        body,
        variables_table);
      break;
    case ir::Op::Type::NoOp:
      BuildNoOp(
        std::static_pointer_cast<ir::NoOp>(op),
        body,
        variables_table);
      break;
    case ir::Op::Type::ReturnOp:
      BuildReturnOp(
        std::static_pointer_cast<ir::ReturnOp>(op),
        body,
        variables_table);
      break;
    case ir::Op::Type::UnaryOp:
      BuildUnaryOp(
        std::static_pointer_cast<ir::UnaryOp>(op),
        body,
        variables_table);
      break;
  }
}

void BuildBinOp(
  std::shared_ptr<ir::BinOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  VariablesTable &variables_table
) {
  // TODO(Lyrositor) Implement
}

void BuildCallOp(
  std::shared_ptr<ir::CallOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  VariablesTable &variables_table
) {
  // Copy, in left-to-right order, the parameters to the registers first and
  // then to the stack before the call
  std::vector<std::shared_ptr<ast::Instruction>> param_setup;
  int64_t stack_size = 0;
  for (size_t idx = 0; idx < op->args.size(); idx++) {
    // Get the source of the parameter
    std::shared_ptr<ast::Operand> source;
    int64_t data_type_size;
    switch (op->args[idx]->operand_type) {
      case ir::Operand::Type::Constant: {
        source = ast::ImmediateOperand::Create(
          std::static_pointer_cast<ir::ConstantOperand>(
            op->args[idx])->value);
        data_type_size = GetDataTypeSize(ir::GetInt64Type());
        break;
      }
      case ir::Operand::Type::Variable: {
        auto variable = std::static_pointer_cast<ir::VariableOperand>(
          op->args[idx])->variable;
        data_type_size = GetDataTypeSize(variable->GetDataType());
        source = variables_table.Get(variable);
        break;
      }
    }

    if (idx < kParameterRegisters.size()) {
      // Copy the parameter's value to its destination register
      std::shared_ptr<ast::Operand> destination = kParameterRegisters[idx];
      param_setup.push_back(
        ast::Instruction::Create(MOVQ, {source, destination}));
    } else {
      // Push the parameter's value to a location on the stack
      param_setup.push_back(ast::Instruction::Create(PUSHQ, {source}));
//      stack_size += data_type_size; // TODO(Lyrositor) Use the appropriate size
      stack_size += kRegisterSize;
    }
  }

  // Store the stack parameters in reverse order
  for (auto rit = param_setup.rbegin(); rit < param_setup.rend(); rit++) {
    body.push_back(*rit);
  }

  // Add the call instruction
  body.push_back(
    ast::Instruction::Create(
      CALL,
      {
        ast::AddressOperand::Create(
          ast::GlobalSymbol::Create(op->function->GetName()))
      }));

  // Restore the stack to its previous state, if parameters were passed on the
  // stack
  if (stack_size > 0) {
    body.push_back(
      ast::Instruction::Create(
        ADDQ,
        {ast::ImmediateOperand::Create(stack_size), RSP}));
  }

  // TODO(Lyrositor) Handle return values
}

void BuildCopyOp(
  std::shared_ptr<ir::CopyOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  VariablesTable &variables_table
) {
  // TODO(Lyrositor) Implement
}

void BuildNoOp(
  std::shared_ptr<ir::NoOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  VariablesTable &variables_table
) {
  UNUSED(op);
  UNUSED(body);
  UNUSED(variables_table);
  body.push_back(ast::Instruction::Create(NOP));
}

void BuildReturnOp(
  std::shared_ptr<ir::ReturnOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  VariablesTable &variables_table
) {
  // TODO(Lyrositor) Implement
}

void BuildUnaryOp(
  std::shared_ptr<ir::UnaryOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  VariablesTable &variables_table
) {
  // TODO(Lyrositor) Implement
}
}  // namespace x64
}  // namespace arch
}  // namespace as
}  // namespace comp
