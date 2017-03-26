#pragma once

#include <memory>
#include <set>
#include <vector>

#include "comp/ir/basic_block.h"
#include "comp/ir/variable.h"

namespace comp {
namespace ir {
class ProgramSymbol {
 public:
  virtual ~ProgramSymbol() = 0;
};

class DataObjectSymbol final : public ProgramSymbol {
 public:
  DataObjectSymbol();
};

/**
 * This represents a C function.
 * TODO: Add a pointer to the AST node for the declaration and definition.
 * If the declaration node is `nullptr`, the function is a builtin.
 */
class FunctionSymbol final : public ProgramSymbol {
 public:
  static std::unique_ptr<FunctionSymbol> Create(
    std::vector<std::shared_ptr<const Variable>> parameters,
    std::shared_ptr<const DataType> return_type,
    std::shared_ptr<BasicBlock> body = nullptr);

  FunctionSymbol(
    std::vector<std::shared_ptr<const Variable>> parameters,
    std::shared_ptr<const DataType> return_type,
    std::shared_ptr<BasicBlock> body = nullptr);

  virtual ~FunctionSymbol();

  std::shared_ptr<BasicBlock> GetBody() const;

  std::vector<std::shared_ptr<const Variable>> GetParameters() const;

  std::shared_ptr<const DataType> GetReturnType() const;

  std::set<std::shared_ptr<const Variable>> GetLocalVariables() const;

  void SetBody(std::shared_ptr<BasicBlock> body);

  void SetLocalVariables(
    std::set<std::shared_ptr<const Variable>> local_variables);

 private:
  std::vector<std::shared_ptr<const Variable>> parameters_;
  const std::shared_ptr<const DataType> return_type_;
  std::shared_ptr<BasicBlock> body_;
  std::set<std::shared_ptr<const Variable>> local_variables_;
};
}  // namespace ir
}  // namespace comp
