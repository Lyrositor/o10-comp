#include <iostream>
#include <string>
#include <comp/ast.h>
#include <comp/exceptions.h>
// Generated with bison by CMake (parser.tab.hpp is in the build directory)
#include "parser.tab.hpp"
// Generated with flex by CMake (lexer.yy.h is in the build directory)
#include "lexer.yy.h"

void yyerror(
  YYLTYPE *locp,
  yyscan_t scanner,
  comp::ast::Program *res,
  const char *msg
) {
  throw comp::ParserException(
    msg,
    std::make_shared<comp::ast::SourceLocation>(
      comp::ast::Position(
        0,
        static_cast<size_t>(locp->first_line - 1),
        static_cast<size_t>(locp->first_column - 1)),
      comp::ast::Position(
        0,
        static_cast<size_t>(locp->last_line - 1),
        static_cast<size_t>(locp->last_column - 1))));
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
}  // namespace parser
}  // namespace comp
