#pragma once

#include <cstddef>
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

struct Op {
  enum class Type {
    Add,
    Copy,
    NoOp
  };

  Op(Type opType);
  virtual ~Op() = 0;

  const Type opType;
};

/**
 * Add the value of the two variables `in1` and `in2` and store the result in `out`.
 */
struct Add final : public Op {
  Add(std::shared_ptr<Variable> out, std::shared_ptr<Variable> in1, std::shared_ptr<Variable> in2);
  virtual ~Add();

  std::shared_ptr<Variable> out;
  std::shared_ptr<Variable> in1;
  std::shared_ptr<Variable> in2;
};

/**
 * Copy the value from `in` to `out`.
 */
struct Copy final : public Op {
  Copy(std::shared_ptr<Variable> out, std::shared_ptr<Variable> in);
  virtual ~Copy();

  std::shared_ptr<Variable> out;
  std::shared_ptr<Variable> in;
};

/*
 * Idempotent operation
 */
struct NoOp final : public Op {
  NoOp();
  virtual ~NoOp();
};
}
}
