#include <comp/parser.h>
#include <iostream>
#include <comp/eval.h>

int main(void) {
  std::shared_ptr<comp::ast::Expression> expression = comp::parser::parse();
  int32_t value = comp::eval::evalExpression(*expression);
  std::cout << value << "\n";
  return 0;
}
