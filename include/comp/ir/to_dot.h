#pragma once

#include <memory>
#include <map>
#include "comp/dot/ast.h"
#include "comp/ir/program.h"


namespace comp {
namespace ir {

class IdentifiersTable {
 public:
  size_t GetFunctionIdentifier(const FunctionSymbol &f);
  size_t GetVariableIdentifier(const Variable &v);
  size_t GetBasicBlockIdentifier(const BasicBlock &bb);

 private:
  size_t counter = 0;
  std::map<const void*, size_t> identifers_map;
};

void EmitOp(const Op &node, std::ostream &out);
void EmitBasicBlock(const BasicBlock &node, std::ostream &out);
std::string BasicBlockToString(const BasicBlock &node);
std::vector<std::shared_ptr<dot::ast::Statement>> BasicBlockToDot(const BasicBlock &node);
std::vector<std::shared_ptr<dot::ast::Statement>> ControlFlowGraphToDot(const ControlFlowGraph &node);
std::vector<std::shared_ptr<dot::ast::Statement>> FunctionSymbolToDot(const FunctionSymbol &node,IdentifiersTable &it);
std::unique_ptr<dot::ast::Graph> ProgramToDot(const Program &node);
}
}
