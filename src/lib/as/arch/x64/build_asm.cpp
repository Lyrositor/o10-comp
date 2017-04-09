#include <comp/as/arch/x64/build_asm.h>

#include <comp/as/arch/x64/stddef.h>
#include <comp/ir/builtins.h>
#include <comp/ast.h>
#include <comp/utils/exceptions.h>
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
  DECQ = ast::Mnemonic::Create("decq"),
  IDIVQ = ast::Mnemonic::Create("idivq"),
  IMULQ = ast::Mnemonic::Create("imulq"),
  JE = ast::Mnemonic::Create("je"),
  JMP = ast::Mnemonic::Create("jmp"),
  LEA = ast::Mnemonic::Create("lea"),
  LEAVEQ = ast::Mnemonic::Create("leaveq"),
  MOVQ = ast::Mnemonic::Create("movq"),
  MOVZBQ = ast::Mnemonic::Create("movzbq"),
  NEGQ = ast::Mnemonic::Create("negq"),
  NOP = ast::Mnemonic::Create("nop"),
  NOTQ = ast::Mnemonic::Create("notq"),
  INCQ = ast::Mnemonic::Create("incq"),
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
  R10 = ast::RegisterOperand::Create("r10"),
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
  BlockTable block_table;
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
      param_copies.push_back(INSTR(MOVQ, {kParameterRegisters[idx], address}));
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

    // Allocate more memory for arrays
    if (variable->GetDataType()->GetType() == ir::DataType::Type::Array) {
      auto array = std::static_pointer_cast<const ir::ArrayDataType>(
        variable->GetDataType());
      //stack += GetDataTypeSize(array->GetItemType()) * array->GetSize();  TODO(Lyrositor) Use the right data type size
      stack += kRegisterQSize * array->GetSize();
    } else {
      stack += kRegisterQSize;
    }
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
    INSTR(PUSHQ, {RBP}),
    INSTR(MOVQ, {RSP, RBP})
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

  // Generate the labels for every block
  std::set<std::shared_ptr<ir::BasicBlock>>
    blocks = node->GetBody()->GetBasicBlocks();
  size_t label = 0;
  for (auto block : blocks) {
    block_table.Register(
      block,
      ast::GlobalSymbol::Create(".L"+std::to_string(label++)));
  }

  // Generate the function body
  // The epilog will be generated when a return statement is encountered; this
  // is a guarantee by the IR
  BuildBasicBlock(
    node->GetBody()->GetSource(), body, block_table, variables_table);

  // Generate every subsequent block
  blocks.erase(node->GetBody()->GetSource());
  for (auto block : blocks) {
    body.push_back(ast::EmptyStatement::Create({block_table.Get(block)}));
    BuildBasicBlock(block, body, block_table, variables_table);
  }
}

void BuildBasicBlock(
  std::shared_ptr<ir::BasicBlock> block,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const BlockTable &block_table,
  const VariablesTable &variables_table
) {
  for (auto op : block->GetOps()) {
    BuildOp(op, block, body, block_table, variables_table);
  }
  if (block->GetType() == ir::BasicBlock::Type::Jump) {
    body.push_back(
      INSTR(
        JMP,
        {ast::AddressOperand::Create(block_table.Get(block->GetBranch()))}));
  }
}

void BuildOp(
  std::shared_ptr<ir::Op> op,
  std::shared_ptr<ir::BasicBlock> block,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const BlockTable &block_table,
  const VariablesTable &variables_table
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
      BuildCastOp(
        std::static_pointer_cast<ir::CastOp>(op),
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
    case ir::Op::Type::TestOp:
      BuildTestOp(
        std::static_pointer_cast<ir::TestOp>(op),
        block,
        body,
        block_table,
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
  const VariablesTable &variables_table
) {
  auto source1 = BuildOperand(op->in1, body, variables_table);
  auto source2 = BuildOperand(op->in2, body, variables_table);
  auto destination = BuildOperand(op->out, body, variables_table);
  body.push_back(INSTR(MOVQ, {source1, RAX}));
  switch (op->binary_operator) {
    case ir::BinOp::BinaryOperator::Addition: {
      // Check if this is actually an indexing operation
      // TODO(Lyrositor) Make this its own operation?
      auto in_data_type = ir::GetOperandType(*op->in1);
      auto out_data_type = ir::GetOperandType(*op->out);
      if (in_data_type->GetType() == ir::DataType::Type::Array &&
        out_data_type->GetType() == ir::DataType::Type::Pointer) {
        auto array = std::static_pointer_cast<const ir::ArrayDataType>(
          in_data_type);
        auto pointer = std::static_pointer_cast<const ir::PointerDataType>(
          out_data_type);
        body.insert(body.end(), {
          INSTR(MOVQ, {source2, RAX}),
          INSTR(IMULQ, {
            ast::ImmediateOperand::Create(
              GetDataTypeSize(array->GetItemType())),
            RAX
          }),
          INSTR(LEA, {source1, RCX}),
          INSTR(ADDQ, {RCX, RAX})
        });
      } else {
        // Otherwise, this is just a normal addition
        body.push_back(INSTR(ADDQ, {source2, RAX}));
      }
      break;
    }
    case ir::BinOp::BinaryOperator::BitwiseAnd:
      body.push_back(INSTR(ANDQ, {source2, RAX}));
      break;
    case ir::BinOp::BinaryOperator::BitwiseOr:
      body.push_back(INSTR(ORQ, {source2, RAX}));
      break;
    case ir::BinOp::BinaryOperator::BitwiseXor:
      body.push_back(INSTR(XORQ, {source2, RAX}));
      break;
    case ir::BinOp::BinaryOperator::Division:
      body.push_back(INSTR(CQTO));
      body.push_back(INSTR(IDIVQ, {source2}));
      break;
    case ir::BinOp::BinaryOperator::Equality:
      body.push_back(INSTR(CMPQ, {source2, RAX}));
      body.push_back(INSTR(SETE, {AL}));
      body.push_back(INSTR(MOVZBQ, {AL, RAX}));
      break;
    case ir::BinOp::BinaryOperator::GreaterThan:
      body.push_back(INSTR(CMPQ, {source2, RAX}));
      body.push_back(INSTR(SETG, {AL}));
      body.push_back(INSTR(MOVZBQ, {AL, RAX}));
      break;
    case ir::BinOp::BinaryOperator::GreaterThanOrEqual:
      body.push_back(INSTR(CMPQ, {source2, RAX}));
      body.push_back(INSTR(SETGE, {AL}));
      body.push_back(INSTR(MOVZBQ, {AL, RAX}));
      break;
    case ir::BinOp::BinaryOperator::Inequality:
      body.push_back(INSTR(CMPQ, {source2, RAX}));
      body.push_back(INSTR(SETNE, {AL}));
      body.push_back(INSTR(MOVZBQ, {AL, RAX}));
      break;
    case ir::BinOp::BinaryOperator::LeftShift:
      body.push_back(INSTR(MOVQ, {source2, RCX}));
      body.push_back(INSTR(SALQ, {CL, RAX}));
      break;
    case ir::BinOp::BinaryOperator::LessThan:
      body.insert(body.end(), {
        INSTR(CMPQ, {source2, RAX}),
        INSTR(SETL, {AL}),
        INSTR(MOVZBQ, {AL, RAX})
      });
      break;
    case ir::BinOp::BinaryOperator::LessThanOrEqualTo:
      body.insert(body.end(), {
        INSTR(CMPQ, {source2, RAX}),
        INSTR(SETLE, {AL}),
        INSTR(MOVZBQ, {AL, RAX})
      });
      break;
    case ir::BinOp::BinaryOperator::Multiplication:
      body.push_back(INSTR(IMULQ, {source2, RAX}));
      break;
    case ir::BinOp::BinaryOperator::Subtraction:
      body.push_back(INSTR(SUBQ, {source2, RAX}));
      break;
    case ir::BinOp::BinaryOperator::Remainder:
      body.push_back(INSTR(CQTO));
      body.push_back(INSTR(IDIVQ, {source2}));
      body.push_back(INSTR(MOVQ, {RDX, RAX}));
      break;
    case ir::BinOp::BinaryOperator::RightShift:
      body.push_back(INSTR(MOVQ, {source2, RCX}));
      body.push_back(INSTR(SARQ, {CL, RAX}));
      break;
  }
  body.push_back(INSTR(MOVQ, {RAX, destination}));
}

void BuildCallOp(
  std::shared_ptr<ir::CallOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const VariablesTable &variables_table
) {
  // Copy, in left-to-right order, the parameters to the registers first and
  // then to the stack before the call
  std::vector<std::shared_ptr<ast::Instruction>> param_setup;
  int64_t stack_size = 0;
  for (size_t idx = 0; idx < op->args.size(); idx++) {
    // Get the source of the parameter
    std::shared_ptr<ast::Operand> source = BuildOperand(
      op->args[idx],
      body,
      variables_table);

    // Pass the array pointer instead of trying to copy by value
    if (op->args[idx]->operand_type == ir::Operand::Type::Variable) {
      auto variable = std::static_pointer_cast<ir::VariableOperand>(
        op->args[idx])->variable;
      if (variable->GetDataType()->GetType() == ir::DataType::Type::Array) {
        body.push_back(
          INSTR(
            LEA, {BuildOperand(op->args[idx], body, variables_table), R10}));
        source = R10;
      }
    }

    if (idx < kParameterRegisters.size()) {
      // Copy the parameter's value to its destination register
      std::shared_ptr<ast::Operand> destination = kParameterRegisters[idx];
      param_setup.push_back(INSTR(MOVQ, {source, destination}));
    } else {
      // Push the parameter's value to a location on the stack
      param_setup.push_back(INSTR(PUSHQ, {source}));
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
      INSTR(ADDQ, {ast::ImmediateOperand::Create(stack_size), RSP}));
  }

  // Store the return value
  auto destination = BuildOperand(op->out, body, variables_table);
  body.push_back(INSTR(MOVQ, {RAX, destination}));
}

void BuildCastOp(
  std::shared_ptr<ir::CastOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const VariablesTable &variables_table
) {
  // TODO(Lyrositor) This is simple CopyOp for now; change this once different
  // types are properly handled
  auto source = BuildOperand(op->in, body, variables_table);
  auto destination = BuildOperand(op->out, body, variables_table);

  // Introduce an intermediary register if this is a copy from memory to memory
  if (source->node_type == ast::Node::Type::MemoryReference &&
    destination->node_type == ast::Node::Type::MemoryReference) {
    body.push_back(INSTR(MOVQ, {source, RAX}));
    body.push_back(INSTR(MOVQ, {RAX, destination}));
  } else {
    body.push_back(INSTR(MOVQ, {source, destination}));
  }
}

void BuildCopyOp(
  std::shared_ptr<ir::CopyOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const VariablesTable &variables_table
) {
  auto source = BuildOperand(op->in, body, variables_table);
  auto destination = BuildOperand(op->out, body, variables_table);

  // Introduce an intermediary register if this is a copy from memory to memory
  if (source->node_type == ast::Node::Type::MemoryReference &&
    destination->node_type == ast::Node::Type::MemoryReference) {
    body.push_back(INSTR(MOVQ, {source, RAX}));
    body.push_back(INSTR(MOVQ, {RAX, destination}));
  } else {
    body.push_back(INSTR(MOVQ, {source, destination}));
  }
}

void BuildNoOp(
  std::shared_ptr<ir::NoOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const VariablesTable &variables_table
) {
  UNUSED(op);
  UNUSED(body);
  UNUSED(variables_table);
  body.push_back(INSTR(NOP));
}

void BuildReturnOp(
  std::shared_ptr<ir::ReturnOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const VariablesTable &variables_table
) {
  // Return the value if this is a typed return
  if (op->in != nullptr) {
    body.push_back(
      INSTR(MOVQ, {BuildOperand(op->in, body, variables_table), RAX}));
  }

  // Epilog
  body.insert(body.end(), {
    INSTR(LEAVEQ),
    INSTR(RETQ)
  });
}

void BuildTestOp(
  std::shared_ptr<ir::TestOp> op,
  std::shared_ptr<ir::BasicBlock> block,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const BlockTable &block_table,
  const VariablesTable &variables_table
) {
  // Jump to the `true` branch if the test is not equal to zero; otherwise,
  // jump to the `false` branch
  auto test = BuildOperand(op->test, body, variables_table);
  body.push_back(INSTR(MOVQ, {test, RAX}));
  body.push_back(INSTR(CMPQ, 0, RAX));
  body.push_back(
    INSTR(
      JE,
      {ast::AddressOperand::Create(
          block_table.Get(block->GetBranchIfFalse()))}));
  body.push_back(
    INSTR(
      JMP,
      {ast::AddressOperand::Create(
          block_table.Get(block->GetBranchIfTrue()))}));
}

void BuildUnaryOp(
  std::shared_ptr<ir::UnaryOp> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const VariablesTable &variables_table
) {
  auto source = BuildOperand(op->in1, body, variables_table);
  auto destination = BuildOperand(op->out, body, variables_table);
  switch (op->unary_operator) {
    case ir::UnaryOp::UnaryOperator::AddressOf:
      throw std::runtime_error("Not implemented: `AddressOf` operation");
    case ir::UnaryOp::UnaryOperator::BitwiseComplement:
      body.push_back(INSTR(MOVQ, {source, RAX}));
      body.push_back(INSTR(NOTQ, {RAX}));
      break;
    case ir::UnaryOp::UnaryOperator::Decrement:
      body.push_back(INSTR(MOVQ, {source, RAX}));
      body.push_back(INSTR(DECQ, {RAX}));
      break;
    case ir::UnaryOp::UnaryOperator::Increment:
      body.push_back(INSTR(MOVQ, {source, RAX}));
      body.push_back(INSTR(INCQ, {RAX}));
      break;
    case ir::UnaryOp::UnaryOperator::LogicalNegation:
      body.push_back(INSTR(MOVQ, {source, RAX}));
      body.push_back(INSTR(CMPQ, {ast::ImmediateOperand::Create(0), RAX}));
      body.push_back(INSTR(SETE, {AL}));
      body.push_back(INSTR(MOVZBQ, {AL, RAX}));
      break;
    case ir::UnaryOp::UnaryOperator::UnaryMinus:
      body.push_back(INSTR(MOVQ, {source, RAX}));
      body.push_back(INSTR(NEGQ, {RAX}));
      break;
  }
  body.push_back(INSTR(MOVQ, {RAX, destination}));
}

std::shared_ptr<ast::Operand> BuildOperand(
  std::shared_ptr<ir::Operand> op,
  std::vector<std::shared_ptr<ast::Statement>> &body,
  const VariablesTable &variables_table
) {
  switch (op->operand_type) {
    case ir::Operand::Type::Variable: {
      return variables_table.Get(
        std::static_pointer_cast<ir::VariableOperand>(op)->variable);
    }
    case ir::Operand::Type::Indirect: {
      std::shared_ptr<ir::Operand> address_op = std::static_pointer_cast<
        ir::IndirectOperand>(op)->address;
      body.push_back(
        INSTR(MOVQ, {BuildOperand(address_op, body, variables_table), R10}));
      return ast::MemoryReference::Create(R10);
    }
    case ir::Operand::Type::Constant: {
      return ast::ImmediateOperand::Create(
        std::static_pointer_cast<ir::ConstantOperand>(op)->value);
    }
  }
  throw Exception("unexpected as operand type");
}
}  // namespace x64
}  // namespace arch
}  // namespace as
}  // namespace comp
