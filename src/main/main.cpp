#include <comp/parser.h>
#include <iostream>
#include <comp/eval.h>
#include <cerrno>
#include <cstring>
#include <string>
#include <fstream>

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Incorrect arguments." << std::endl;
  } else {
    std::ifstream ifs(argv[1]);
    if (ifs.fail()) {
      std::cerr << strerror(errno) << std::endl;
    } else {
      std::string content( (std::istreambuf_iterator<char>(ifs) ),
                           (std::istreambuf_iterator<char>()    ) );
      std::shared_ptr<comp::ast::RExpression> expression = comp::parser::parse(content);
      int64_t value = comp::eval::eval_expression(*expression);
      std::cout << value << "\n";
    }
  }
  return 0;
}
