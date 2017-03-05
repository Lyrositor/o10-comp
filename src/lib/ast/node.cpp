#include <comp/ast/node.h>

namespace comp {
  namespace ast {
    Position::Position(size_t index_, size_t line_, size_t column_) :
      index(index_), line(line_), column(column_) {}

    SourceLocation::SourceLocation(const Position &start_, const Position &end_) :
      start(start_), end(end_) {}

    Node::Node(NodeType type_, std::shared_ptr<SourceLocation> location_) :
      type(type_), location(location_) {}

    Expression::Expression(NodeType type_, std::shared_ptr<SourceLocation> location_) :
      Node(type_, location_) {}

    Literal::Literal(int32_t value_, std::shared_ptr<SourceLocation> location_) :
      Expression(NodeType::LiteralType, location_), value(value_) {}

    std::shared_ptr<Literal> Literal::create(int32_t value, std::shared_ptr<SourceLocation> location) {
      return std::shared_ptr<Literal>(new Literal(value, location));
    }

    BinaryExpression::BinaryExpression(BinaryOperator op_, std::shared_ptr<Expression> left_,
                                       std::shared_ptr<Expression> right_, std::shared_ptr<SourceLocation> location_) :
      Expression(BinaryExpressionType, location_), op(op_), left(left_), right(right_) {}

    std::shared_ptr<BinaryExpression> BinaryExpression::create(BinaryOperator operator_,
                                                               std::shared_ptr<Expression> left,
                                                               std::shared_ptr<Expression> right,
                                                               std::shared_ptr<SourceLocation> location) {
      return std::shared_ptr<BinaryExpression>(new BinaryExpression(operator_, left, right, location));
    }
  }
}
