#include "gtest/gtest.h"
#include <comp/parser.h>
#include <comp/eval.h>
#include <cstddef>
#include <sstream>
#include <iomanip>

TEST(comp__parser__parser, BinaryExpression) {
  std::shared_ptr<comp::ast::Expression> expr = comp::parser::parse("123+456");
  EXPECT_EQ(579, comp::eval::eval_expression(*expr));
}

TEST(comp__parser__parser, CharLiteralFromSourceChar) {
  std::shared_ptr<comp::ast::Expression> expr = comp::parser::parse("'a'");
  EXPECT_EQ(comp::ast::Node::Type::Uint8Literal, expr->nodeType);
  std::shared_ptr<comp::ast::Uint8Literal> uint8Literal = std::static_pointer_cast<comp::ast::Uint8Literal>(expr);
  EXPECT_EQ('a', uint8Literal->value);
}

TEST(comp__parser__parser, CharLiteralFromOctalEscape) {
  uint8_t i = 0;
  do {
    std::stringstream input_stream;
    input_stream << std::setbase(8) << "'\\" << uint64_t(i) << "'";
    std::string input(input_stream.str());
    std::shared_ptr<comp::ast::Expression> expr = comp::parser::parse(input);
    EXPECT_EQ(comp::ast::Node::Type::Uint8Literal, expr->nodeType);
    std::shared_ptr<comp::ast::Uint8Literal> uint8Literal = std::static_pointer_cast<comp::ast::Uint8Literal>(expr);
    EXPECT_EQ(i, uint8Literal->value);
  } while (i++ < 255);
}
