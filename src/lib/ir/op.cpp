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

std::unique_ptr<Call> Call::Create(std::shared_ptr<VariableOperand> out, std::shared_ptr<ir::FunctionSymbol> function, std::vector<std::shared_ptr<Operand>> args) {
  return std::unique_ptr<Call>(new Call(out, function, args));
}

Call::Call (
  std::shared_ptr<VariableOperand> out,
  std::shared_ptr<ir::FunctionSymbol> function,
  std::vector<std::shared_ptr<Operand>> args
) :
  Op(Op::Type::Call),
  out(out),
  function(function),
  args(args) {
}
Call::~Call() {
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
  return std::unique_ptr<UnaryOp>(new UnaryOperator(out, unaryOperator, in1));
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

std::unique_ptr<Copy> Copy::Create(std::shared_ptr<VariableOperand> out, std::shared_ptr<Operand> in) {
  return std::unique_ptr<Copy>(new Copy(out, in));
}

Copy::Copy(
  std::shared_ptr<VariableOperand> out,
  std::shared_ptr<Operand> in
) :
  Op(Op::Type::Copy),
  out(out),
  in(in) {
}

Copy::~Copy() {
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
