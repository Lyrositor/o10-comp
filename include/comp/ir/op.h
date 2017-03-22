#pragma once

#include <cstddef>
#include "comp/ir/variable.h"

namespace comp{
namespace ir {
//enum class RegisterType {
//  Int8,
//  Int16,
//  Int32,
//  Int64,
//  Address,
//  Float32,
//  Float64,
//};

struct Operand {
  enum class Type {
    Variable,
    Constant
  };
  Operand(Type operand_type);

  virtual ~Operand() = 0;

  const Type operand_type;
};

struct VariableOperand final: Operand {
  static std::unique_ptr<VariableOperand> Create(const std::shared_ptr<const Variable> variable);
  VariableOperand(const std::shared_ptr<const Variable> variable);
  ~VariableOperand();
  const std::shared_ptr<const Variable> variable;
};

struct ConstantOperand final: Operand {
  static std::unique_ptr<ConstantOperand> Create(int64_t value);
  ConstantOperand(int64_t value);
  ~ConstantOperand();
  int64_t value;
};

struct Op {
  enum class Type {
    Add,
    Copy,
    Comp,
    NoOp
  };

  Op(Type op_type);
  virtual ~Op() = 0;

  const Type op_type;
};

/**
 * Add the value of the two variables `in1` and `in2` and store the result in `out`.
 */
struct Add final : public Op {
  static std::unique_ptr<Add> Create(std::shared_ptr<VariableOperand> out, std::shared_ptr<Operand> in1, std::shared_ptr<Operand> in2);
  Add(std::shared_ptr<VariableOperand> out, std::shared_ptr<Operand> in1, std::shared_ptr<Operand> in2);
  virtual ~Add();

  std::shared_ptr<VariableOperand> out;
  std::shared_ptr<Operand> in1;
  std::shared_ptr<Operand> in2;
};

/**
 * Copy the value from `in` to `out`.
 */
struct Copy final : public Op {
  static std::unique_ptr<Copy> Create(std::shared_ptr<VariableOperand> out, std::shared_ptr<Operand> in);
  Copy(std::shared_ptr<VariableOperand> out, std::shared_ptr<Operand> in);
  virtual ~Copy();

  std::shared_ptr<VariableOperand> out;
  std::shared_ptr<Operand> in;
};

/**
 * Compare value `val` to non-zero
 */
struct Comp final : public Op {
  Comp(std::shared_ptr<Variable> val);
  virtual ~Comp();

  std::shared_ptr<Variable> val;
};

/*
 * Idempotent operation
 */
struct NoOp final : public Op {
  static std::unique_ptr<NoOp> Create();
  NoOp();
  virtual ~NoOp();
};
}  // namespace ir
}  // namespace comp
