#pragma once

#include <memory>
#include <map>
#include "comp/dot/ast.h"
#include "comp/ir/program.h"


namespace comp {
namespace ir {

class IdentifiersTable final {
 public:
  IdentifiersTable();
  ~IdentifiersTable();

  std::string GetBasicBlockId(const BasicBlock &bb);
  std::string GetFunctionId(const FunctionSymbol &function_synbol);
  std::string GetVariableId(const Variable &v);

 private:
  size_t basic_blocks_counter;
  std::map<const BasicBlock*, size_t> basic_blocks_map;
  size_t functions_counter;
  std::map<const FunctionSymbol*, size_t> functions_map;
  size_t variables_counter;
  std::map<const Variable*, size_t> variables_map;
};

void EmitVariableOperand(const VariableOperand &node, std::ostream &out, IdentifiersTable &it);
void EmitIndirectOperand(const IndirectOperand &node, std::ostream &out, IdentifiersTable &it);
void EmitOperand(const Operand &node, std::ostream &out, IdentifiersTable &it);
void EmitConstantOperand(const ConstantOperand &node, std::ostream &out);
std::string BinaryOperatorToString(const BinOp::BinaryOperator &node);
void EmitOp(const Op &node, std::ostream &out);
void EmitBasicBlock(const BasicBlock &node, std::ostream &out);
std::string BasicBlockToString(const BasicBlock &node);
std::vector<std::shared_ptr<dot::ast::Statement>> BasicBlockToDot(const BasicBlock &node);
std::vector<std::shared_ptr<dot::ast::Statement>> ControlFlowGraphToDot(const ControlFlowGraph &node);
std::vector<std::shared_ptr<dot::ast::Statement>> FunctionSymbolToDot(const FunctionSymbol &node,IdentifiersTable &it);
std::unique_ptr<dot::ast::Graph> ProgramToDot(const Program &node);
}
}
