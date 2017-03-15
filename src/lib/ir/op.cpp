#include <comp/ir/op.h>

namespace comp {
namespace ir {
Op::Op(Type op_type) : op_type(op_type) {
}

Add::Add(
  std::shared_ptr<Variable> out,
  std::shared_ptr<Variable> in1,
  std::shared_ptr<Variable> in2
) :
  Op(Op::Type::Add),
  out(out),
  in1(in1),
  in2(in2) {
}

Add::~Add() {
}

Copy::Copy(
  std::shared_ptr<Variable> out,
  std::shared_ptr<Variable> in
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
}
}
