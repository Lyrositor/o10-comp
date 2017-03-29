#pragma once

#include <cstddef>

#include <comp/ast/program.h>

#define YYLTYPE_IS_DECLARED 1

struct YYLTYPE;
union YYSTYPE;

typedef struct YYLTYPE {
  size_t first_line = 0;
  size_t first_column = 0;
  size_t first_index = 0;
  size_t last_line = 0;
  size_t last_column = 0;
  size_t last_index = 0;
} YYLTYPE;

void yyerror(YYLTYPE *, void *scanner, comp::ast::Program *, const char *);
int yylex(YYSTYPE *lvalp, YYLTYPE * yylloc, void *scanner);
void yy_scan_string(const char *str);
