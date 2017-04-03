#include <comp/ir/op.h>

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

std::unique_ptr<VariableOperand> VariableOperand::Create(const std::shared_ptr<const Variable> variable) {
  return std::unique_ptr<VariableOperand>(new VariableOperand(variable));
}

VariableOperand::VariableOperand(const std::shared_ptr<const Variable> variable) : Operand(Type::Variable), variable(variable) {
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

std::unique_ptr<CallOp> CallOp::Create(std::shared_ptr<VariableOperand> out, std::shared_ptr<ir::FunctionSymbol> function, std::vector<std::shared_ptr<Operand>> args) {
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
  std::shared_ptr<VariableOperand> out,
  BinaryOperator binaryOperator,
  std::shared_ptr<Operand> in1,
  std::shared_ptr<Operand> in2) {
  return std::unique_ptr<BinOp>(new BinOp(out, binaryOperator, in1, in2));
}

BinOp::BinOp(
  std::shared_ptr<VariableOperand> out,
  BinaryOperator binaryOperator,
  std::shared_ptr<Operand> in1,
  std::shared_ptr<Operand> in2
) :
  Op(Op::Type::BinOp),
  out(out),
  binaryOperator(binaryOperator),
  in1(in1),
  in2(in2) {
}

BinOp::~BinOp() {
}

std::unique_ptr<UnaryOp> UnaryOp::Create(std::shared_ptr<VariableOperand> out,
                                         UnaryOp::UnaryOperator unaryOperator,
                                         std::shared_ptr<Operand> in1) {
  return std::unique_ptr<UnaryOp>(new UnaryOp(out, unaryOperator, in1));
}

UnaryOp::UnaryOp(std::shared_ptr<VariableOperand> out,
                 UnaryOp::UnaryOperator unaryOperator,
                 std::shared_ptr<Operand> in1
) :
  Op(Op::Type::UnaryOp),
  out(out),
  unaryOperator(unaryOperator),
  in1(in1) {
}

UnaryOp::~UnaryOp() {
}

std::unique_ptr<CopyOp> CopyOp::Create(std::shared_ptr<VariableOperand> out, std::shared_ptr<Operand> in) {
  return std::unique_ptr<CopyOp>(new CopyOp(out, in));
}

CopyOp::CopyOp(
  std::shared_ptr<VariableOperand> out,
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


}
}
