#pragma once

#include <string>

#include "comp/ast/declarator.h"
#include "comp/ast/expression.h"

namespace comp {
namespace ast {
struct ArrayDeclarator final : public Declarator {
  static std::unique_ptr<ArrayDeclarator> Create(
    std::shared_ptr<Declarator> declarator,
    std::shared_ptr<RExpression> size,
    std::shared_ptr<SourceLocation> location = nullptr);

  ArrayDeclarator(
    std::shared_ptr<Declarator> declarator,
    std::shared_ptr<RExpression> size,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~ArrayDeclarator();

  std::string GetName() override;

  std::shared_ptr<Declarator> declarator_;

  /**
   * `size` is the `nullptr` if the size is unknown.
   */
  const std::shared_ptr<RExpression> size;
};
}  // namespace ast
}  // namespace comp
