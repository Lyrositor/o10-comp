#pragma once

#include <comp/ir/program.h>
#include <set>

namespace comp {
namespace ir {
namespace optimizer {
enum class Optimization {
  /**
   * Eliminate NoOp branches
   */
  NoOpElimination,

  /**
   * Compute constant expressions
   */
  ConstantsPropagation,

  /**
   * Ensure that the function contain a single return operation
   */
  ReturnFactorization
};

/**
 * @param program The original program
 * @param optimizations The set of optimizations to apply
 * @return The optimized program
 */
std::unique_ptr<ir::Program> OptimizeProgram(
  const ir::Program &program,
  const std::set<Optimization> &optimizations);

/**
 * Optimize a function symbol
 */
std::unique_ptr<ir::FunctionSymbol> OptimizeFunctionSymbol(
  const ir::FunctionSymbol &function,
  const std::set<Optimization> &optimizations);

/**
 * Optimize a single control flow graph
 */
std::unique_ptr<ir::ControlFlowGraph> OptimizeControlFlowGraph(
  const ir::ControlFlowGraph &cfg,
  const std::set<Optimization> &optimizations);

} // namespace optimizer
} // namespace ir
} // namespace comp
