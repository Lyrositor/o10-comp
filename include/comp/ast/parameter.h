#pragma once

#include "comp/ast/data_type.h"
#include "comp/ast/declaration.h"
#include "comp/ast/declarator.h"
#include "comp/ast/literal_data_type.h"

namespace comp {
namespace ast {
struct Parameter final : public Node {
  static std::unique_ptr<Parameter> Create(
    std::shared_ptr<LiteralDataType> data_type,
    std::shared_ptr<Declarator> declarator,
    std::shared_ptr<SourceLocation> location = nullptr);

  Parameter(
    std::shared_ptr<LiteralDataType> data_type,
    std::shared_ptr<Declarator> declarator,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~Parameter();

  const std::shared_ptr<LiteralDataType> data_type;
  const std::shared_ptr<Declarator> declarator;
};
}  // namespace ast
}  // namespace comp
