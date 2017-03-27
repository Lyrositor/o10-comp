#include <comp/ir/op.h>

namespace comp {
namespace ir {
Op::Op(Type op_type) : op_type(op_type) {
}

Operand::Operand(Type operand_type) : operand_type(operand_type) {
}

std::unique_ptr<VariableOperand> VariableOperand::Create(std::shared_ptr<Variable> variable) {
  return std::unique_ptr<VariableOperand>(new VariableOperand(variable));
}

VariableOperand::VariableOperand(std::shared_ptr<Variable> variable) : Operand(Type::Variable), variable(variable) {
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

std::unique_ptr<Add> Add::Create(std::shared_ptr<VariableOperand> out,
                                 std::shared_ptr<Operand> in1,
                                 std::shared_ptr<Operand> in2) {
  return std::unique_ptr<Add>(new Add(out, in1, in2));
}

Add::Add(
  std::shared_ptr<VariableOperand> out,
  std::shared_ptr<Operand> in1,
  std::shared_ptr<Operand> in2
) :
  Op(Op::Type::Add),
  out(out),
  in1(in1),
  in2(in2) {
}

Add::~Add() {
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
