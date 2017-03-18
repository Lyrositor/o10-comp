#include <comp/parser.h>
#include <iostream>
#include <comp/eval.h>

int main(void) {
  std::shared_ptr<comp::ast::RExpression> expression = comp::parser::parse("123+456");
  int64_t value = comp::eval::eval_expression(*expression);
  std::cout << value << "\n";
  return 0;
}
