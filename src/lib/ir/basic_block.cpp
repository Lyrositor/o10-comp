#include <comp/ir/basic_block.h>

namespace comp {
namespace ir {
std::unique_ptr<BasicBlock> BasicBlock::Create(
  std::vector<std::shared_ptr<Op>> ops) {
  return std::unique_ptr<BasicBlock>(new BasicBlock(std::move(ops)));
}

BasicBlock::BasicBlock(
  std::vector<std::shared_ptr<Op>> ops
) :
  ops_(std::move(ops)),
  type_(Type::Incomplete),
  branch_if_false_(),
  branch_if_true_() {
}

std::vector<std::shared_ptr<Op>> BasicBlock::GetOps() const {
  return std::vector<std::shared_ptr<Op>>(this->ops_.begin(), this->ops_.end());
}

BasicBlock::Type BasicBlock::GetType() const {
  return this->type_;
}

void BasicBlock::Push(std::shared_ptr<Op> op) {
  if (this->type_ != Type::Incomplete) {
    throw std::runtime_error("Invalid `type` for the current `BasicBlock`, required `Incomplete` for `Push`");
  }
  this->ops_.push_back(op);
}

void BasicBlock::SetFinal() {
  if (this->type_ != Type::Incomplete) {
    throw std::runtime_error("Invalid `type` for the current `BasicBlock`, required `Incomplete` for `SetFinal`");
  }
  if (this->ops_.size() == 0) {
    this->ops_.push_back(NoOp::Create());
  }
  this->type_ = Type::Final;
}

void BasicBlock::SetJump(std::shared_ptr<BasicBlock> branch) {
  if (this->type_ != Type::Incomplete) {
    throw std::runtime_error("Invalid `type` for the current `BasicBlock`, required `Incomplete` for `SetJump`");
  }
  this->type_ = Type::Jump;
  this->branch_if_true_ = branch;
}

void BasicBlock::SetConditionalJump(
  std::shared_ptr<Operand> test,
  std::shared_ptr<BasicBlock> branch_if_true,
  std::shared_ptr<BasicBlock> branch_if_false
) {
  if (this->type_ != Type::Incomplete) {
    throw std::runtime_error(
      "Invalid `type` for the current `BasicBlock`, required `Incomplete` for `SetConditionalJump`");
  }
  this->type_ = Type::ConditionalJump;
  this->ops_.push_back(TestOp::Create(test));
  this->branch_if_true_ = branch_if_true;
  this->branch_if_false_ = branch_if_false;
}

void BasicBlock::SetReturn(std::shared_ptr<Operand> return_value) {
  if (this->type_ != Type::Incomplete) {
    throw std::runtime_error(
      "Invalid `type` for the current `BasicBlock`, required `Incomplete` for `SetReturn`");
  }
  this->type_ = Type::Return;
  this->ops_.push_back(ReturnOp::Create(return_value));
}

std::shared_ptr<BasicBlock> BasicBlock::GetBranch() const {
  if (this->type_ != Type::Jump) {
    throw std::runtime_error("Invalid `type` for the current `BasicBlock`, required `Jump` for `GetBranch`");
  }
  std::shared_ptr<BasicBlock> result = this->branch_if_true_.lock();
  if (result == nullptr) {
    throw std::runtime_error("Basic Block with `Jump` type has `nullptr` branch");
  }
  return result;
}

std::shared_ptr<Operand> BasicBlock::GetTest() const {
  if (this->type_ != Type::ConditionalJump) {
    throw std::runtime_error("Invalid `type` for the current `BasicBlock`, required `ConditionalJump` for `GetTest`");
  } else if (this->ops_.size() == 0) {
    throw std::runtime_error("Basic Block with `ConditionalJump` type has an empty operations list");
  }
  std::shared_ptr<Op> last_op = this->ops_[this->ops_.size() - 1];
  if (last_op->op_type != Op::Type::TestOp) {
    throw std::runtime_error("Basic Block with `ConditionalJump` type does not end with a `TestOp` operation");
  }
  std::shared_ptr<Operand> test_operand = std::static_pointer_cast<TestOp>(last_op)->test;
  if (test_operand == nullptr) {
    throw std::runtime_error("Basic Block with `ConditionalJump` ends with a `TestOp` containing the `nullptr`");
  }
  return test_operand;
}

std::shared_ptr<BasicBlock> BasicBlock::GetBranchIfTrue() const {
  if (this->type_ != Type::ConditionalJump) {
    throw std::runtime_error(
      "Invalid `type` for the current `BasicBlock`, required `ConditionalJump` for `GetBranchIfTrue`");
  }
  std::shared_ptr<BasicBlock> result = this->branch_if_true_.lock();
  if (result == nullptr) {
    throw std::runtime_error("Basic Block with `ConditionalJump` type has `nullptr` branch_if_true");
  }
  return result;
}

std::shared_ptr<BasicBlock> BasicBlock::GetBranchIfFalse() const {
  if (this->type_ != Type::ConditionalJump) {
    throw std::runtime_error(
      "Invalid `type` for the current `BasicBlock`, required `ConditionalJump` for `GetBranchIfFalse`");
  }
  std::shared_ptr<BasicBlock> result = this->branch_if_false_.lock();
  if (result == nullptr) {
    throw std::runtime_error("Basic Block with `ConditionalJump` type has `nullptr` branch_if_false");
  }
  return result;
}

std::shared_ptr<Operand> BasicBlock::GetReturnValue() const {
  if (this->type_ != Type::Return) {
    throw std::runtime_error("Invalid `type` for the current `BasicBlock`, required `Return` for `GetReturnValue`");
  } else if (this->ops_.size() == 0) {
    throw std::runtime_error("Basic Block with `Return` type has an empty operations list");
  }
  std::shared_ptr<Op> last_op = this->ops_[this->ops_.size() - 1];
  if (last_op->op_type != Op::Type::ReturnOp) {
    throw std::runtime_error("Basic Block with `Return` type does not end with a `ReturnOp` operation");
  }
  return std::static_pointer_cast<ReturnOp>(last_op)->in;
}

BasicBlock::~BasicBlock() {
}
}  // namespace ir
}  // namespace comp
