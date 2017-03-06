%{
#include <stdio.h>
#include <stdlib.h>
#include <comp/ast.h>
#include "parser.tab.h"
%}
%option noyywrap
integerLiteralPattern [0-9]+
%%
[ \n\t]      {/* ignore */}
{integerLiteralPattern}     {yylval.i = atoi(yytext); return INTEGER_LITERAL;}
"+"          {return ADDITION_OPERATOR;}
"-"          {return SUBTRACTION_OPERATOR;}
"/"          {return DIVISION_OPERATOR;}
"*"          {return MULTIPLICATION_OPERATOR;}
"%"          {return REMAINDER_OPERATOR;}
