#include <comp/as/arch/x64/build_asm.h>

#include <comp/as/arch/x64/stddef.h>
#include <comp/ir/builtins.h>
#include <comp/ast.h>
#include <comp/exceptions.h>
#include <comp/utils.h>

namespace comp {
namespace as {
namespace arch {
namespace x64 {
#define INSTR(...) ast::Instruction::Create(__VA_ARGS__)

// Define the x86-64 mnemonics to be used
static const std::shared_ptr<ast::Mnemonic>
  ADDQ = ast::Mnemonic::Create("addq"),
  ANDQ = ast::Mnemonic::Create("andq"),
  CALLQ = ast::Mnemonic::Create("callq"),
  CMPQ = ast::Mnemonic::Create("cmpq"),
  CQTO = ast::Mnemonic::Create("cqto"),
  IDIVQ = ast::Mnemonic::Create("idivq"),
  IMULQ = ast::Mnemonic::Create("imulq"),
  LEAVEQ = ast::Mnemonic::Create("leaveq"),
  MOVQ = ast::Mnemonic::Create("movq"),
  MOVZBQ = ast::Mnemonic::Create("movzbq"),
  NEGQ = ast::Mnemonic::Create("negq"),
  NOP = ast::Mnemonic::Create("nop"),
  NOTQ = ast::Mnemonic::Create("notq"),
  ORQ = ast::Mnemonic::Create("orq"),
  PUSHQ = ast::Mnemonic::Create("pushq"),
  RETQ = ast::Mnemonic::Create("retq"),
  SALQ = ast::Mnemonic::Create("salq"),
  SARQ = ast::Mnemonic::Create("sarq"),
  SETE = ast::Mnemonic::Create("sete"),
  SETG = ast::Mnemonic::Create("setg"),
  SETGE = ast::Mnemonic::Create("setge"),
  SETL = ast::Mnemonic::Create("setl"),
  SETLE = ast::Mnemonic::Create("setle"),
  SETNE = ast::Mnemonic::Create("setne"),
  SUBQ = ast::Mnemonic::Create("subq"),
  XORQ = ast::Mnemonic::Create("xorq");

// Define the x86-64 to be used
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
  RSI = ast::RegisterOperand::Create("rsi"),

  AL = ast::RegisterOperand::Create("al"),
  CL = ast::RegisterOperand::Create("cl");

// Define the registers to be used to pass parameters
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
  // kParameterRegisters (in left-to-right order). On Windows, these are copied
  // to the shadow space created before the function call; otherwise, they're
  // added to the function stack.
  // All subsequent parameters are pushed on to the stack before the return
  // address and the old RBP (in right-to-left order).
  int64_t param_stack = kRegisterQSize * 2;
  int64_t stack = 0;
  std::vector<std::shared_ptr<ast::Instruction>> param_copies;
  for (size_t idx = 0; idx < params.size(); idx++) {
    std::shared_ptr<ast::MemoryReference> address;

    // Copy the parameter's value if it came from a register
    if (idx < kParameterRegisters.size()) {
#ifdef WIN32
      address = ast::MemoryReference::Create(
        RBP, ast::BigIntegerLiteral::Create(param_stack));
      param_stack += kRegisterQSize;
#else
      stack += kRegisterQSize;
      address = ast::MemoryReference::Create(
        RBP, ast::BigIntegerLiteral::Create(-stack));
#endif  // WIN32
      param_copies.push_back(INSTR(MOVQ, { kParameterRegisters[idx], address }));
    } else {
      address = ast::MemoryReference::Create(
        RBP, ast::BigIntegerLiteral::Create(param_stack));
      //param_stack += GetDataTypeSize(params[idx]->GetDataType()); TODO(Lyrositor) Use the right data type size
      param_stack += kRegisterQSize;
    }
    variables_table.Register(params[idx], address);
  }

  // Store the memory references of the other local variables on the stack
  // The bottom of the stack (highest addresses) are reserved for the register
  // parameters, even if there are none to be copied.
  for (auto variable : node->GetLocalVariables()) {
    if (variables_table.Contains(variable)) {  // Don't count the parameters
      continue;
    }
    //stack += GetDataTypeSize(variable->GetDataType());  TODO(Lyrositor) Use the right data type size
    stack += kRegisterQSize;
    variables_table.Register(
      variable,
      ast::MemoryReference::Create(
        RBP,
        ast::BigIntegerLiteral::Create(-stack)));
  }

  // Prolog
  std::shared_ptr<ast::GlobalSymbol> symbol = ast::GlobalSymbol::Create(
    node->GetName());
  body.insert(body.end(), {
    ast::GlobalDirective::Create(symbol),
    ast::EmptyStatement::Create({symbol}),
    INSTR(PUSHQ, { RBP }),
    INSTR(MOVQ, { RSP, RBP })
  });
  body.push_back(INSTR(SUBQ, stack, RSP));

  // Copy the register parameters, in reverse order on Windows
#ifdef WIN32
  auto it = param_copies.rbegin();
  auto end = param_copies.rend();
#else
  auto it = param_copies.begin();
  auto end = param_copies.end();
#endif  // WIN32
  for (; it != end; it++) {
    body.push_back(*it);
  }

  // Generate the function body
  // The epilog will be generated when a return statement is encountered; this
  // is a guarantee by the IR
  BuildBasicBlock(node->GetBody()->GetSource(), body, variables_table);

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
    case ir::Op::Type::CastOp:
      // TODO(Lyrositor) Implement cast op
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
    case ir::Op::Type::TestOp:
      // TODO(Lyrositor) Implement test op
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
  auto source1 = BuildOperand(op->in1, variables_table);
  auto source2 = BuildOperand(op->in2, variables_table);
  auto destination = BuildOperand(op->out, variables_table);
  body.push_back(INSTR(MOVQ, { source1, RAX }));
  switch (op->binary_operator) {
    case ir::BinOp::BinaryOperator::Addition:body.push_back(INSTR(ADDQ, { source2, RAX }));
      break;
    case ir::BinOp::BinaryOperator::BitwiseAnd:body.push_back(INSTR(ANDQ, { source2, RAX }));
      break;
    case ir::BinOp::BinaryOperator::BitwiseOr:body.push_back(INSTR(ORQ, { source2, RAX }));
      break;
    case ir::BinOp::BinaryOperator::BitwiseXor:body.push_back(INSTR(XORQ, { source2, RAX }));
      break;
    case ir::BinOp::BinaryOperator::Division:body.push_back(INSTR(CQTO));
      body.push_back(INSTR(IDIVQ, { source2 }));
      break;
    case ir::BinOp::BinaryOperator::Equality:body.push_back(INSTR(CMPQ, { source2, RAX }));
      body.push_back(INSTR(SETE, { AL }));
      body.push_back(INSTR(MOVZBQ, { AL, RAX }));
      break;
    case ir::BinOp::BinaryOperator::GreaterThan:body.push_back(INSTR(CMPQ, { source2, RAX }));
      body.push_back(INSTR(SETG, { AL }));
      body.push_back(INSTR(MOVZBQ, { AL, RAX }));
      break;
    case ir::BinOp::BinaryOperator::GreaterThanOrEqual:body.push_back(INSTR(CMPQ, { source2, RAX }));
      body.push_back(INSTR(SETGE, { AL }));
      body.push_back(INSTR(MOVZBQ, { AL, RAX }));
      break;
    case ir::BinOp::BinaryOperator::Inequality:body.push_back(INSTR(CMPQ, { source2, RAX }));
      body.push_back(INSTR(SETNE, { AL }));
      body.push_back(INSTR(MOVZBQ, { AL, RAX }));
      break;
    case ir::BinOp::BinaryOperator::LeftShift:body.push_back(INSTR(MOVQ, { source2, RCX }));
      body.push_back(INSTR(SALQ, { CL, RAX }));
      break;
    case ir::BinOp::BinaryOperator::LessThan:
      body.insert(body.end(), {
        INSTR(CMPQ, { source2, RAX }),
        INSTR(SETL, { AL }),
        INSTR(MOVZBQ, { AL, RAX })
      });
      break;
    case ir::BinOp::BinaryOperator::LessThanOrEqualTo:
      body.insert(body.end(), {
        INSTR(CMPQ, { source2, RAX }),
        INSTR(SETLE, { AL }),
        INSTR(MOVZBQ, { AL, RAX })
      });
      break;
    case ir::BinOp::BinaryOperator::Multiplication:body.push_back(INSTR(IMULQ, { source2, RAX }));
      break;
    case ir::BinOp::BinaryOperator::Subtraction:body.push_back(INSTR(SUBQ, { source2, RAX }));
      break;
    case ir::BinOp::BinaryOperator::Remainder:body.push_back(INSTR(CQTO));
      body.push_back(INSTR(IDIVQ, { source2 }));
      body.push_back(INSTR(MOVQ, { RDX, RAX }));
      break;
    case ir::BinOp::BinaryOperator::RightShift:body.push_back(INSTR(MOVQ, { source2, RCX }));
      body.push_back(INSTR(SARQ, { CL, RAX }));
      break;
  }
  body.push_back(INSTR(MOVQ, { RAX, destination }));
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
    // int64_t data_type_size;
    switch (op->args[idx]->operand_type) {
      case ir::Operand::Type::Constant: {
        source = ast::ImmediateOperand::Create(
          std::static_pointer_cast<ir::ConstantOperand>(
            op->args[idx])->value);
        // data_type_size = GetDataTypeSize(ir::GetInt64Type());
        break;
      }
      case ir::Operand::Type::Variable: {
        auto variable = std::static_pointer_cast<ir::VariableOperand>(
          op->args[idx])->variable;
        // data_type_size = GetDataTypeSize(variable->GetDataType());
        source = variables_table.Get(variable);
        break;
      }
      default: {
        throw std::runtime_error("Unexpected value for `op->args[idx]->operand_type` in `BuildCallOp`");
      }
    }

    if (idx < kParameterRegisters.size()) {
      // Copy the parameter's value to its destination register
      std::shared_ptr<ast::Operand> destination = kParameterRegisters[idx];
      param_setup.push_back(INSTR(MOVQ, { source, destination }));
    } else {
      // Push the parameter's value to a location on the stack
      param_setup.push_back(INSTR(PUSHQ, { source }));
//     stack_size += data_type_size; TODO(Lyrositor) Use the appropriate size
      stack_size += kRegisterQSize;
    }
  }

  // Store the stack parameters in reverse order
  for (auto rit = param_setup.rbegin(); rit < param_setup.rend(); rit++) {
    body.push_back(*rit);
  }

  // Add the call instruction
#ifdef WIN32
  // On Windows, the calling convention requires the creation of a shadow space
  // before the function call on the stack
  std::shared_ptr<ast::ImmediateOperand> shadow_space =
    ast::ImmediateOperand::Create(kParameterRegisters.size() * kRegisterQSize);
  body.push_back(INSTR(SUBQ, {shadow_space, RSP}));
  stack_size += shadow_space->value;
#endif  // WIN32
  body.push_back(
    INSTR(
      CALLQ,
      {
        ast::AddressOperand::Create(
          ast::GlobalSymbol::Create(op->function->GetName()))
      }));

  // Restore the stack to its previous state, if parameters were passed on the
  // stack
  if (stack_size > 0) {
    body.push_back(
      INSTR(ADDQ, { ast::ImmediateOperand::Create(stack_size), RSP }));
  }

  // Store the return value
  auto destination = BuildOperand(op->out, variables_table);
  body.push_back(INSTR(MOVQ, { RAX, destination }));
}

void BuildCopyOp(
  std::shared_ptr<ir::CopyOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  VariablesTable &variables_table
) {
  auto source = BuildOperand(op->in, variables_table);
  auto destination = BuildOperand(op->out, variables_table);

  // Introduce an intermediary register if this is a copy from memory to memory
  if (source->node_type == ast::Node::Type::MemoryReference &&
    destination->node_type == ast::Node::Type::MemoryReference) {
    body.push_back(INSTR(MOVQ, { source, RAX }));
    body.push_back(INSTR(MOVQ, { RAX, destination }));
  } else {
    body.push_back(INSTR(MOVQ, { source, destination }));
  }
}

void BuildNoOp(
  std::shared_ptr<ir::NoOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  VariablesTable &variables_table
) {
  UNUSED(op);
  UNUSED(body);
  UNUSED(variables_table);
  body.push_back(INSTR(NOP));
}

void BuildReturnOp(
  std::shared_ptr<ir::ReturnOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  VariablesTable &variables_table
) {
  // Return the value if this is a typed return
  if (op->in != nullptr) {
    body.push_back(INSTR(MOVQ, { BuildOperand(op->in, variables_table), RAX }));
  }

  // Epilog
  body.insert(body.end(), {
    INSTR(LEAVEQ),
    INSTR(RETQ)
  });
}

void BuildUnaryOp(
  std::shared_ptr<ir::UnaryOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  VariablesTable &variables_table
) {
  auto source = BuildOperand(op->in1, variables_table);
  auto destination = BuildOperand(op->out, variables_table);
  switch (op->unary_operator) {
    case ir::UnaryOp::UnaryOperator::BitwiseComplement:
      body.insert(
        body.end(),
        {INSTR(MOVQ, { source, RAX }), INSTR(NOTQ, { RAX })});
      break;
    case ir::UnaryOp::UnaryOperator::LogicalNegation:
      body.insert(
        body.end(),
        {INSTR(CMPQ, 0, source), INSTR(SETE, { AL }), INSTR(MOVZBQ, { AL, RAX })});
      break;
    case ir::UnaryOp::UnaryOperator::UnaryMinus:
      body.insert(
        body.end(),
        {INSTR(MOVQ, { source, RAX }), INSTR(NEGQ, { RAX })});
      break;
  }
  body.push_back(INSTR(MOVQ, { RAX, destination }));
}

std::shared_ptr<ast::Operand> BuildOperand(
  std::shared_ptr<ir::Operand> op,
  VariablesTable &variables_table
) {
  switch (op->operand_type) {
    case ir::Operand::Type::Variable: {
      return variables_table.Get(
        std::static_pointer_cast<ir::VariableOperand>(op)->variable);
    }
    case ir::Operand::Type::Constant: {
      return ast::ImmediateOperand::Create(
        std::static_pointer_cast<ir::ConstantOperand>(op)->value);
    }
    default: {
      throw std::runtime_error("Unexpected value for `op->args[idx]->operand_type` in `BuildCallOp`");
    }
  }
}
}  // namespace x64
}  // namespace arch
}  // namespace as
}  // namespace comp
