#pragma once

#include <memory>
#include <vector>

#include "comp/ir/op.h"

namespace comp {
namespace ir {
class BasicBlock {
 public:
  enum class Type {
    /**
     * This basic block is not complete.
     */
      Incomplete,

    /**
     * This basic block is a dead-end.
     */
      Final,

    /**
     * This basic block leads to an other basic block.
     */
      Jump,

    /**
     * There are two possible next basick blocks. The destination is chosen
     * depending on a test operand.
     */
      ConditionalJump,

    /**
     * This basic returns a value from the current function.
     */
      Return
  };

  /**
   * @return Unique pointer on an `Incomplete` basic block.
   */
  static std::unique_ptr<BasicBlock> Create(
    std::vector<std::shared_ptr<Op>> ops = std::vector<std::shared_ptr<Op>>());

  /**
   * An `Incomplete` basic block.
   */
  BasicBlock(
    std::vector<std::shared_ptr<Op>> ops = std::vector<std::shared_ptr<Op>>());

  virtual ~BasicBlock();

  /**
   * @return A copy of the operations list for thie basic block
   */
  std::vector<std::shared_ptr<Op>> GetOps() const;

  /**
   * @return The current type (state) of the basic block.
   */
  Type GetType() const;

  /**
   * Push a new operation at the end of the basic block.
   *
   * Requires the `Incomplete` type, otherwise throws a runtine error.
   *
   * @param op next operation
   */
  void Push(std::shared_ptr<Op> op);

  /**
   * Changes the type to `Final`
   *
   * Requires the `Incomplete` type, otherwise throws a runtine error.
   */
  void SetFinal();

  /**
   * Changes the type to `Jump`
   *
   * Requires the `Incomplete` type, otherwise throws a runtine error.
   *
   * @param branch The next basic block
   */
  void SetJump(std::shared_ptr<BasicBlock> branch);

  /**
   * Changes the type to `ConditionalJump`
   *
   * This adds a `Test` operation at the end of the block, using the provided operand.
   *
   * Requires the `Incomplete` type, otherwise throws a runtine error.
   *
   * @param test Test operand
   * @param branch_if_true Next basic block if the test operand is non-zero
   * @param branch_if_false Next basic block if the test operand is zero
   */
  void SetConditionalJump(
    std::shared_ptr<Operand> test,
    std::shared_ptr<BasicBlock> branch_if_true,
    std::shared_ptr<BasicBlock> branch_if_false
  );

  /**
   * Changes the type to `Return`
   *
   * This adds a `Return` operation at the end of the block, using the provided operand.
   *
   * Requires the `Incomplete` type, otherwise throws a runtine error.
   *
   * @param return_value Return value operand
   */
  void SetReturn(
    std::shared_ptr<Operand> return_value
  );

  /**
   * Requires the `Jump` type, otherwise throws a runtine error.
   *
   * Guarantees a non-null pointer.
   *
   * @return Next basic block
   */
  std::shared_ptr<BasicBlock> GetBranch() const;

  /**
   * Requires the `ConditionalJump` type, otherwise throws a runtine error.
   *
   * Guarantees a non-null pointer.
   *
   * @return The test operand for the conditional jump
   */
  std::shared_ptr<Operand> GetTest() const;

  /**
   * Requires the `ConditionalJump` type, otherwise throws a runtine error.
   *
   * Guarantees a non-null pointer.
   *
   * @return Basic block if the test operand is non-zero.
   */
  std::shared_ptr<BasicBlock> GetBranchIfTrue() const;

  /**
   * Requires the `ConditionalJump` type, otherwise throws a runtine error.
   *
   * Guarantees a non-null pointer.
   *
   * @return Basic block if the test operand is zero.
   */
  std::shared_ptr<BasicBlock> GetBranchIfFalse() const;

  /**
   * Requires the `Return` type, otherwise throws a runtine error.
   *
   * Guarantees a non-null pointer.
   *
   * @return The return value operand for the `Return` operation of the current basic block. Nullable.
   */
  std::shared_ptr<Operand> GetReturnValue() const;

 private:
  /**
   * The current type (state) of this basic block
   */
   Type type_;

  /**
   * The list of simple operations associated to this basic block
   */
  std::vector<std::shared_ptr<Op>> ops_;

  /**
   * `Incomplete` -> `nullptr`
   * `Final` -> `nullptr`
   * `Jump` -> return value for `GetBranch`
   * `ConditionalJump` -> return value for `GetBranchIfTrue`
   * `Return` -> `nullptr`
   */
  std::weak_ptr<BasicBlock> branch_if_true_;
  /**
   * `Incomplete` -> `nullptr`
   * `Final` -> `nullptr`
   * `Jump` -> `nullptr`
   * `ConditionalJump` -> return value for `GetBranchIfFalse`
   * `Return` -> `nullptr`
   */
  std::weak_ptr<BasicBlock> branch_if_false_;
};
} // namespace ir
} // namespace comp
