#pragma once

#include <cstddef>
#include <memory>
#include "position.h"


namespace comp {
  namespace ast {
    enum class NodeType {
      BinaryExpression,
      ArrayExpression,
      Literal
    };

    class Node {
      public:
        Node(NodeType type, std::shared_ptr<SourceLocation> location);
        virtual ~Node();

        const NodeType type;
        const std::shared_ptr<SourceLocation> location;
    };
  }
}
