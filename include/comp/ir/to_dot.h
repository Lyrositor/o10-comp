#pragma once

#include <memory>
#include "comp/dot/ast.h"
#include "comp/ir/program.h"

namespace comp {
namespace ir {
void EmitOp(const Op &node, std::ostream &out);
void EmitBasicBlock(const BasicBlock &node, std::ostream &out);
std::string BasicBlockToString(const BasicBlock &node);
std::vector<std::shared_ptr<dot::ast::Statement>> BasicBlockToDot(const BasicBlock &node);
std::vector<std::shared_ptr<dot::ast::Statement>> ControlFlowGraphToDot(const ControlFlowGraph &node);
std::vector<std::shared_ptr<dot::ast::Statement>> FunctionSymbolToDot(const FunctionSymbol &node);
std::unique_ptr<dot::ast::Graph> ProgramToDot(const Program &node);
}
}
