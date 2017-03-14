#pragma once

#include "declaration.h"
#include "identifier.h"

namespace comp {
namespace ast {
struct Parameter final : public Node {
  Parameter(
    std::shared_ptr<DataType> dataType,
    std::shared_ptr<Identifier> identifier,
    std::shared_ptr<SourceLocation> location = nullptr
  );
  virtual ~Parameter();

  const std::shared_ptr<DataType> dataType;
  const std::shared_ptr<Identifier> identifier;
};
}
}
