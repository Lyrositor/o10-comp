#pragma once

#include "declaration.h"
#include "identifier.h"

namespace comp {
namespace ast {
struct Parameter final : public Node {
  static std::unique_ptr<Parameter> Create(
    std::shared_ptr<DataType> dataType,
    std::shared_ptr<Identifier> identifier,
    std::shared_ptr<SourceLocation> location = nullptr
  );

  Parameter(
    std::shared_ptr<DataType> dataType,
    std::shared_ptr<Identifier> identifier,
    std::shared_ptr<SourceLocation> location = nullptr
  );

  ~Parameter();

  const std::shared_ptr<DataType> dataType;
  const std::shared_ptr<Identifier> identifier;
};
}
}
