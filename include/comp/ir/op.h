#pragma once

#include <cstddef>
#include <vector>
#include "variable.h"



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
    BinOp,
    CallOp,
    CastOp,
    CopyOp,
    NoOp,
    ReturnOp,
    TestOp,
    UnaryOp
  };

  Op(Type op_type);
  virtual ~Op() = 0;

  const Type op_type;
};

class FunctionSymbol;
/**
 * Call a function `function` with arguments `args` and store the result in `out`
 */
struct CallOp final : public Op {
  static std::unique_ptr<CallOp> Create(std::shared_ptr<VariableOperand> out, std::shared_ptr<ir::FunctionSymbol> function, std::vector<std::shared_ptr<Operand>> args);
  CallOp(std::shared_ptr<VariableOperand> out, std::shared_ptr<ir::FunctionSymbol> function, std::vector<std::shared_ptr<Operand>> args);
  virtual ~CallOp();

  std::shared_ptr<VariableOperand> out;
  std::shared_ptr<ir::FunctionSymbol> function;
  std::vector<std::shared_ptr<Operand>> args;
};

/**
 * Compute the value of the two variables `in1` and `in2` transformed with the operator `binaryOperator` and store the result in `out`.
 */
struct BinOp final : public Op {
  enum class BinaryOperator {
    Addition, // left + right
    BitwiseAnd, // left & right
    BitwiseOr, // left | right
    BitwiseXor, // left ^ right
    Division, // left / right
    Equality, // left == right
    GreaterThan, // left > right
    GreaterThanOrEqual, // left >= right
    Inequality, // left != right
    LeftShift, // left << right
    LessThan, // left < right
    LessThanOrEqualTo, // left <= right
    Multiplication, // left * right
    Remainder, // left % right
    RightShift, // left >> right
    Subtraction // left - right
  };

  static std::unique_ptr<BinOp> Create(std::shared_ptr<VariableOperand> out, BinaryOperator binaryOperator, std::shared_ptr<Operand> in1, std::shared_ptr<Operand> in2);
  BinOp(std::shared_ptr<VariableOperand> out, BinaryOperator binaryOperator, std::shared_ptr<Operand> in1, std::shared_ptr<Operand> in2);
  virtual ~BinOp();

  std::shared_ptr<VariableOperand> out;
  BinaryOperator binary_operator;
  std::shared_ptr<Operand> in1;
  std::shared_ptr<Operand> in2;
};

/**
 * Compute the value of the variable `in1` transformed with the operator `unaryOperator` and store the result in `out`.
 */
struct UnaryOp final : public Op {
  enum class UnaryOperator {
    BitwiseComplement, // ~expression
    LogicalNegation, // !expression
    UnaryMinus, // -expression
  };

  static std::unique_ptr<UnaryOp> Create(std::shared_ptr<VariableOperand> out, UnaryOperator unaryOperator, std::shared_ptr<Operand> in1);
  UnaryOp(std::shared_ptr<VariableOperand> out, UnaryOperator unaryOperator, std::shared_ptr<Operand> in1);
  virtual ~UnaryOp();

  std::shared_ptr<VariableOperand> out;
  UnaryOperator unaryOperator;
  std::shared_ptr<Operand> in1;
};

/**
 * Copy the value from `in` to `out`, perform a cast during the copy.
 */
struct CastOp final : public Op {
  static std::unique_ptr<CastOp> Create(std::shared_ptr<VariableOperand> out, std::shared_ptr<Operand> in);
  CastOp(std::shared_ptr<VariableOperand> out, std::shared_ptr<Operand> in);
  virtual ~CastOp();

  std::shared_ptr<VariableOperand> out;
  std::shared_ptr<Operand> in;
};

/**
 * Copy the value from `in` to `out`.
 */
struct CopyOp final : public Op {
  static std::unique_ptr<CopyOp> Create(std::shared_ptr<VariableOperand> out, std::shared_ptr<Operand> in);
  CopyOp(std::shared_ptr<VariableOperand> out, std::shared_ptr<Operand> in);
  virtual ~CopyOp();

  std::shared_ptr<VariableOperand> out;
  std::shared_ptr<Operand> in;
};

/**
 * Leave the function and return the `in` value or nothing if `in` is a nullptr
 */
struct ReturnOp final : public Op {
  static std::unique_ptr<ReturnOp> Create(std::shared_ptr<Operand> in);
  ReturnOp(std::shared_ptr<Operand> in);
  virtual ~ReturnOp();

  std::shared_ptr<Operand> in;
};

/**
 * Final operation of a BasicBlock if its type is `ConditionalJump`.
 */
struct TestOp final : public Op {
  static std::unique_ptr<TestOp> Create(std::shared_ptr<Operand> test);
  TestOp(std::shared_ptr<Operand> test);
  virtual ~TestOp();

  /**
   * If this operand is equal to 0, use the `branchIfFalse`; otherwise use the `branchIfTrue`.
   */
  std::shared_ptr<Operand> test;
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
