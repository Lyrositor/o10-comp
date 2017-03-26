#pragma once

#include "comp/ast/data_type.h"
#include "comp/ast/declaration.h"
#include "comp/ast/declarator.h"
#include "comp/ast/literal_data_type.h"

namespace comp {
namespace ast {
struct Parameter : public Node {
  Parameter(Type node_type, std::shared_ptr<SourceLocation> location);

  virtual ~Parameter() = 0;
};

struct NamedParameter final : public Parameter {
  static std::unique_ptr<NamedParameter> Create(
    std::shared_ptr<LiteralDataType> data_type,
    std::shared_ptr<Declarator> declarator,
    std::shared_ptr<SourceLocation> location = nullptr);

  NamedParameter(
    std::shared_ptr<LiteralDataType> data_type,
    std::shared_ptr<Declarator> declarator,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~NamedParameter();

  const std::shared_ptr<LiteralDataType> data_type;
  const std::shared_ptr<Declarator> declarator;
};

struct AnonymousParameter final : public Parameter {
  static std::unique_ptr<AnonymousParameter> Create(
    std::shared_ptr<DataType> data_type,
    std::shared_ptr<SourceLocation> location = nullptr);

  AnonymousParameter(
    std::shared_ptr<DataType> data_type,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~AnonymousParameter();

  const std::shared_ptr<DataType> data_type;
};
}  // namespace ast
}  // namespace comp
