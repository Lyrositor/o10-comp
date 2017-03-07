#pragma once

#include "expression.h"

namespace comp {
  namespace ast {
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

        virtual ~BinaryExpression();

        const BinaryOperator op;
        std::shared_ptr<Expression> left;
        std::shared_ptr<Expression> right;

        static std::shared_ptr<BinaryExpression> create(BinaryOperator operator_, std::shared_ptr<Expression> left,
                                                        std::shared_ptr<Expression> right,
                                                        std::shared_ptr<SourceLocation> location);
    };
  }
}
