//#include <iostream>
//#include <comp/ast.h>
//
//int main() {
//  std::cout << comp::ast::create_node() << "\n";
//  return 0;
//}

#include <comp/parser.h>
#include <iostream>

int main(void) {
  std::cout << doParse() << "\n";
  return 0;
}
