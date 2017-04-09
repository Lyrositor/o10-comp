#include <comp/ir/op.h>

#include <comp/ir/builtins.h>

namespace comp {
namespace ir {
Op::Op(Type op_type) : op_type(op_type) {
}

Op::~Op() {
}

Operand::Operand(Type operand_type) : operand_type(operand_type) {
}

Operand::~Operand() {
}

WritableOperand::WritableOperand(Type operand_type) : Operand(operand_type) {
}

WritableOperand::~WritableOperand() {
}

std::unique_ptr<VariableOperand> VariableOperand::Create(const std::shared_ptr<const Variable> variable) {
  return std::unique_ptr<VariableOperand>(new VariableOperand(variable));
}

VariableOperand::VariableOperand(
  const std::shared_ptr<const Variable> variable
) :
  WritableOperand(Type::Variable),
  variable(variable) {
}

VariableOperand::~VariableOperand() {
}

std::unique_ptr<ConstantOperand> ConstantOperand::Create(int64_t value) {
  return std::unique_ptr<ConstantOperand>(new ConstantOperand(value));
}

ConstantOperand::ConstantOperand(int64_t value) : Operand(Type::Constant), value(value) {
}

ConstantOperand::~ConstantOperand() {
}

std::unique_ptr<IndirectOperand> IndirectOperand::Create(
  const std::shared_ptr<Operand> address) {
  return std::unique_ptr<IndirectOperand>(new IndirectOperand(address));
}

IndirectOperand::IndirectOperand(
  const std::shared_ptr<Operand> address
) :
  WritableOperand(Type::Indirect), address(address) {
}

IndirectOperand::~IndirectOperand() {
}

std::unique_ptr<CallOp> CallOp::Create(
  std::shared_ptr<VariableOperand> out,
  std::shared_ptr<ir::FunctionSymbol> function,
  std::vector<std::shared_ptr<Operand>> args) {
  return std::unique_ptr<CallOp>(new CallOp(out, function, args));
}

CallOp::CallOp(
  std::shared_ptr<VariableOperand> out,
  std::shared_ptr<ir::FunctionSymbol> function,
  std::vector<std::shared_ptr<Operand>> args
) :
  Op(Op::Type::CallOp),
  out(out),
  function(function),
  args(args) {
}

CallOp::~CallOp() {
}

std::unique_ptr<BinOp> BinOp::Create(
  std::shared_ptr<WritableOperand> out,
  BinaryOperator binaryOperator,
  std::shared_ptr<Operand> in1,
  std::shared_ptr<Operand> in2) {
  return std::unique_ptr<BinOp>(new BinOp(out, binaryOperator, in1, in2));
}

BinOp::BinOp(
  std::shared_ptr<WritableOperand> out,
  BinaryOperator binaryOperator,
  std::shared_ptr<Operand> in1,
  std::shared_ptr<Operand> in2
) :
  Op(Op::Type::BinOp),
  out(out),
  binary_operator(binaryOperator),
  in1(in1),
  in2(in2) {
}

BinOp::~BinOp() {
}

std::unique_ptr<UnaryOp> UnaryOp::Create(std::shared_ptr<WritableOperand> out,
                                         UnaryOp::UnaryOperator unaryOperator,
                                         std::shared_ptr<Operand> in1) {
  return std::unique_ptr<UnaryOp>(new UnaryOp(out, unaryOperator, in1));
}

UnaryOp::UnaryOp(std::shared_ptr<WritableOperand> out,
                 UnaryOp::UnaryOperator unaryOperator,
                 std::shared_ptr<Operand> in1
) :
  Op(Op::Type::UnaryOp),
  out(out),
  unary_operator(unaryOperator),
  in1(in1) {
}

UnaryOp::~UnaryOp() {
}

std::unique_ptr<CastOp> CastOp::Create(std::shared_ptr<WritableOperand> out, std::shared_ptr<Operand> in) {
  return std::unique_ptr<CastOp>(new CastOp(out, in));
}

CastOp::CastOp(
  std::shared_ptr<WritableOperand> out,
  std::shared_ptr<Operand> in
) :
  Op(Op::Type::CastOp),
  out(out),
  in(in) {
}

CastOp::~CastOp() {
}

std::unique_ptr<CopyOp> CopyOp::Create(std::shared_ptr<WritableOperand> out, std::shared_ptr<Operand> in) {
  return std::unique_ptr<CopyOp>(new CopyOp(out, in));
}

CopyOp::CopyOp(
  std::shared_ptr<WritableOperand> out,
  std::shared_ptr<Operand> in
) :
  Op(Op::Type::CopyOp),
  out(out),
  in(in) {
}

CopyOp::~CopyOp() {
}

std::unique_ptr<ReturnOp> ReturnOp::Create(std::shared_ptr<Operand> in) {
  return std::unique_ptr<ReturnOp>(new ReturnOp(in));
}

ReturnOp::ReturnOp(std::shared_ptr<Operand> in) :
  Op(Op::Type::ReturnOp),
  in(in) {
}

ReturnOp::~ReturnOp() {
}

std::unique_ptr<TestOp> TestOp::Create(std::shared_ptr<Operand> test) {
  return std::unique_ptr<TestOp>(new TestOp(test));
}

TestOp::TestOp(std::shared_ptr<Operand> test) :
  Op(Op::Type::TestOp),
  test(test) {
}

TestOp::~TestOp() {
}

NoOp::NoOp() : Op(Op::Type::NoOp) {
}

NoOp::~NoOp() {
}

std::unique_ptr<NoOp> NoOp::Create() {
  return std::unique_ptr<NoOp>(new NoOp());
}

const std::shared_ptr<const DataType> GetOperandType(const Operand &operand) {
  switch (operand.operand_type) {
    case Operand::Type::Variable: {
      return static_cast<const VariableOperand &>(operand).variable->GetDataType();
    }
    case Operand::Type::Indirect: {
      std::shared_ptr<const DataType> base_type = GetOperandType(*static_cast<const IndirectOperand &>(operand).address);
      switch (base_type->GetType()) {
        case DataType::Type::Array: {
          return std::static_pointer_cast<const ArrayDataType>(base_type)->GetItemType();
        }
        case DataType::Type::Pointer: {
          return std::static_pointer_cast<const PointerDataType>(base_type)->GetItemType();
        }
        default: {
          throw std::domain_error("Unexpected value for `base_type->GetType()` in `GetOperandType`");
        }
      }
    }
    case Operand::Type::Constant: {
      return GetInt64Type();
    }
    default: {
      throw std::domain_error("Unexpected value for `operand.operand_type` in `GetOperandType`");
    }
  }
}
}  // ir
}  // comp
