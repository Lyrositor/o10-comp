#pragma once

#include <cstddef>
#include <memory>


namespace comp {
  namespace ast {
    class Position {
      public:
        Position(size_t index, size_t line, size_t column);

        const size_t index;
        const size_t line;
        const size_t column;
    };

    class SourceLocation {
      public:
        SourceLocation(const Position &start, const Position &end);

        const Position start;
        const Position end;
    };

    enum NodeType {
      BinaryExpressionType,
      ArrayExpressionType,
      LiteralType
    };

    class Node {
      public:
        Node(NodeType type, std::shared_ptr<SourceLocation> location);

        const NodeType type;
        const std::shared_ptr<SourceLocation> location;
    };

    class Expression : public Node {
      public:
        Expression(NodeType type, std::shared_ptr<SourceLocation> location);
    };

    class Literal : public Expression {
      public:
        Literal(int32_t value, std::shared_ptr<SourceLocation> location);

        const int32_t value;

        static std::shared_ptr<Literal> create(int32_t value, std::shared_ptr<SourceLocation> location);
    };

//    class ArrayExpression : public Expression {
//      public:
//        ArrayExpression(std::shared_ptr <SourceLocation> location);
//    };

    enum BinaryOperator {
      AdditionOperator,
      SubtractionOperator,
      DivisionOperator,
      MultiplicationOperator,
      RemainderOperator
    };

    class BinaryExpression : public Expression {
      public:
        BinaryExpression(BinaryOperator operator_, std::shared_ptr<Expression> left,
                         std::shared_ptr<Expression> right, std::shared_ptr<SourceLocation> location);

        const BinaryOperator op;
        std::shared_ptr<Expression> left;
        std::shared_ptr<Expression> right;

        static std::shared_ptr<BinaryExpression> create(BinaryOperator operator_, std::shared_ptr<Expression> left,
                                                        std::shared_ptr<Expression> right,
                                                        std::shared_ptr<SourceLocation> location);
    };
  }
}
