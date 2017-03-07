#include <comp/ast.h>
#include "parser.tab.h"
#include "lexer.yy.h"

void yyerror(yyscan_t scanner, comp::ast::Expression *res, const char *msg) {
  printf("Syntax error : %s\n", msg);
}

namespace comp {
  namespace parser {
    std::shared_ptr<comp::ast::Expression> parse() {
      yyscan_t scanner;
      int initResult = yylex_init(&scanner);
      comp::ast::Expression *root = nullptr;
      yy_scan_string("123+456", scanner);
      yyparse(scanner, root);
      yylex_destroy(scanner);
      return std::shared_ptr<comp::ast::Expression>(root);
    }
  }
}
