#pragma once

#include "expression.h"

namespace comp {
  namespace ast {
    class Literal : public Expression {
      public:
        Literal(int32_t value, std::shared_ptr<SourceLocation> location);

        virtual ~Literal();

        const int32_t value;

        static std::shared_ptr<Literal> create(int32_t value, std::shared_ptr<SourceLocation> location);
    };
  }
}
