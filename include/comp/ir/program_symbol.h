#pragma once

#include <memory>
#include <set>
#include <vector>

#include "comp/ir/basic_block.h"
#include "comp/ir/control_flow_graph.h"
#include "comp/ir/variable.h"

namespace comp {
namespace ir {
class ProgramSymbol {
 public:
  enum class Type {
    DataObject,
    Function
  };

  ProgramSymbol(Type type);

  virtual ~ProgramSymbol() = 0;

  Type GetType() const;

 protected:
  Type type_;
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
    const std::string &name,
    std::vector<std::shared_ptr<const Variable>> parameters,
    std::shared_ptr<const DataType> return_type,
    std::shared_ptr<ControlFlowGraph> body = nullptr);

  FunctionSymbol(
    const std::string &name,
    std::vector<std::shared_ptr<const Variable>> parameters,
    std::shared_ptr<const DataType> return_type,
    std::shared_ptr<ControlFlowGraph> body = nullptr);

  virtual ~FunctionSymbol();

  std::string GetName() const;

  std::shared_ptr<ControlFlowGraph> GetBody() const;

  std::vector<std::shared_ptr<const Variable>> GetParameters() const;

  std::shared_ptr<const DataType> GetReturnType() const;

  std::vector<std::shared_ptr<const Variable>> GetLocalVariables() const;

  void SetBody(std::shared_ptr<ControlFlowGraph> body);

  void SetLocalVariables(
    std::vector<std::shared_ptr<const Variable>> local_variables);

 private:
  const std::string name_;
  std::vector<std::shared_ptr<const Variable>> parameters_;
  const std::shared_ptr<const DataType> return_type_;
  std::shared_ptr<ControlFlowGraph> body_;
  std::vector<std::shared_ptr<const Variable>> local_variables_;
};
}  // namespace ir
}  // namespace comp
