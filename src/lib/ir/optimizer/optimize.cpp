#include <comp/ir/optimizer/optimize.h>
#include <comp/utils.h>
#include <comp/ir/optimizer/op_graph.h>

namespace comp {
namespace ir {
namespace optimizer {
std::unique_ptr<ir::Program> OptimizeProgram(
  const ir::Program &program,
  const std::unordered_set<Optimization> &optimizations
) {
  std::unique_ptr<ir::Program> result = ir::Program::Create();

  for (auto symbol: program.GetSymbols()) {
    switch (symbol->GetType()) {
      case ir::ProgramSymbol::Type::Function: {
        result->AddSymbol(OptimizeFunctionSymbol(*std::static_pointer_cast<const FunctionSymbol>(symbol), optimizations));
        break;
      }
      default: {
        result->AddSymbol(symbol);
      }
    }
  }

  return result;
}

std::unique_ptr<ir::FunctionSymbol> OptimizeFunctionSymbol(
  const ir::FunctionSymbol &function,
  const std::unordered_set<Optimization> &optimizations
) {
  std::shared_ptr<ControlFlowGraph> body = OptimizeControlFlowGraph(*function.GetBody(), optimizations);
  std::unique_ptr<ir::FunctionSymbol> result = FunctionSymbol::Create(function.GetName(), function.GetParameters(), function.GetReturnType(), body);
  result->SetLocalVariables(function.GetLocalVariables());
  return result;
}

std::unique_ptr<ir::ControlFlowGraph> OptimizeControlFlowGraph(
  const ir::ControlFlowGraph &cfg,
  const std::unordered_set<Optimization> &optimizations
) {
  UNUSED(optimizations);
  return OpGraph::FromControlFlowGraph(cfg)->ToControlFlowGraph();
}
}  // namespace optimizer
}  // namespace ir
}  // namespace comp
