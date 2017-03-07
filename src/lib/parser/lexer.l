%{

#include <stdio.h>
#include <stdlib.h>
#include <comp/ast.h>
#include "parser.tab.h"

%}

%option 8bit
%option bison-bridge
/* %option debug */
%option pointer
/* %option nodefault */
%option noinput
%option nounput
%option noyywrap
%option reentrant
%option warn

integerLiteralPattern [0-9]+

%%

[ \n\t]      {/* ignore */}
{integerLiteralPattern}     {yylval->i = atoi(yytext); return INTEGER_LITERAL;}
"+"          {return ADDITION_OPERATOR;}
"-"          {return SUBTRACTION_OPERATOR;}
"/"          {return DIVISION_OPERATOR;}
"*"          {return MULTIPLICATION_OPERATOR;}
"%"          {return REMAINDER_OPERATOR;}