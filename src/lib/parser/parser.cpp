#include <string>
#include <comp/ast.h>
// Generated with bison by CMake (parser.tab.hpp is in the build directory)
#include "parser.tab.hpp"
// Generated with flex by CMake (lexer.yy.h is in the build directory)
#include "lexer.yy.h"

void yyerror(yyscan_t scanner, comp::ast::Program *res, const char *msg) {
  throw std::runtime_error(std::string("Syntax error : %s\n") + msg);
}

namespace comp {
namespace parser {
std::shared_ptr<comp::ast::Program> parse(const std::string &input) {
  yyscan_t scanner;
  int initResult = yylex_init(&scanner);
  comp::ast::Program *root = nullptr;
  yy_scan_string(input.c_str(), scanner);
  yyparse(scanner, root);
  yylex_destroy(scanner);
  return std::shared_ptr<comp::ast::Program>(root);
}
}
}
