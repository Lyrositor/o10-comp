#pragma once

#include "comp/ast/statement.h"

namespace comp {
namespace ast {
struct NullStatement final : public Statement {
  static std::unique_ptr<NullStatement> Create(
    std::shared_ptr<SourceLocation> location = nullptr);

  NullStatement(std::shared_ptr<SourceLocation> location = nullptr);

  ~NullStatement();
};
}  // namespace ast
}  // namespace comp
