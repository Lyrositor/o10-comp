#include <iostream>
#include <comp/ast.h>

int main() {
  std::cout << comp::ast::create_node() << "\n";
  return 0;
}
