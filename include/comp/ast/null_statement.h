#pragma once

#include "statement.h"
namespace comp {
namespace ast {
struct NullStatement final : public Statement {
  static std::unique_ptr<NullStatement> Create(
    std::shared_ptr<SourceLocation> location = nullptr
  );

  NullStatement(
    std::shared_ptr<SourceLocation> location = nullptr
  );
  ~NullStatement();
};
}
}
