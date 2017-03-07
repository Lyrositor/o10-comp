#pragma once

#include "node.h"

namespace comp {
  namespace ast {
    class Expression : public Node {
      public:
        Expression(NodeType type, std::shared_ptr<SourceLocation> location);

        virtual ~Expression();
    };
  }
}
