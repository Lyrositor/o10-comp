#pragma once

#include <memory>
#include <vector>
#include "block_statement.h"
#include "declaration.h"
#include "parameter.h"
#include "identifier.h"

namespace comp {
namespace ast {

/**
 * This node represents a function declaration or a function definition at the root of the program.
 * If this node is a function declaration, then `body` is `nullptr`, otherwise if it is a function definition then
 * body is a non-null pointer to a BlockStatement.
 */
struct Function final : public Declaration {
  Function(
    std::shared_ptr<Identifier> identifier,
    std::vector<std::shared_ptr<Parameter>> parameters,
    std::shared_ptr<BlockStatement> body,
    std::shared_ptr<SourceLocation> location = nullptr
  );
  virtual ~Function();

  const std::shared_ptr<Identifier> identifier;
  const std::vector<std::shared_ptr<Parameter>> parameters;
  const std::shared_ptr<BlockStatement> body;
};
}
}
