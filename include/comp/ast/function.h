#pragma once

#include <memory>
#include <vector>

#include "comp/ast/block_statement.h"
#include "comp/ast/data_type.h"
#include "comp/ast/declaration.h"
#include "comp/ast/identifier.h"
#include "comp/ast/parameter.h"

namespace comp {
namespace ast {

/**
 * This node represents a function declaration or a function definition at the
 * root of the program.
 * If this node is a function declaration, then `body` is `nullptr`, otherwise
 * if it is a function definition then body is a non-null pointer to a
 * BlockStatement.
 */
struct Function final : public Declaration {
  static std::unique_ptr<Function> Create(
    std::shared_ptr<Identifier> identifier,
    std::vector<std::shared_ptr<Parameter>> parameters,
    std::shared_ptr<DataType> return_type,
    std::shared_ptr<BlockStatement> body,
    std::shared_ptr<SourceLocation> location = nullptr);

  Function(
    std::shared_ptr<Identifier> identifier,
    std::vector<std::shared_ptr<Parameter>> parameters,
    std::shared_ptr<DataType> return_type,
    std::shared_ptr<BlockStatement> body,
    std::shared_ptr<SourceLocation> location = nullptr);
  ~Function();

  const std::shared_ptr<Identifier> identifier;
  const std::vector<std::shared_ptr<Parameter>> parameters;
  const std::shared_ptr<DataType> return_type;
  const std::shared_ptr<BlockStatement> body;
};
}  // namespace ast
}  // namespace comp
