%{

#include <cstdio>
#include <stdlib.h>
#include <comp/ast.h>
// Generated with bison by CMake (parser.tab.hpp is in the build directory)
#include "parser.tab.hpp"

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

%x charLiteral

integerLiteralPattern [0-9]+

%%

[ \n\t]                           {/* ignore */}
{integerLiteralPattern}           {yylval->i = atoi(yytext); return INTEGER_LITERAL;}
"+"                               {return ADDITION_OPERATOR;}
"-"                               {return SUBTRACTION_OPERATOR;}
"/"                               {return DIVISION_OPERATOR;}
"*"                               {return MULTIPLICATION_OPERATOR;}
"%"                               {return REMAINDER_OPERATOR;}

<INITIAL>"'"                      {BEGIN(charLiteral); return SIMPLE_QUOTE;}
<charLiteral>{
  [^\\'\n]                        {yylval->uint8 = yytext[0]; return SOURCE_CHAR;}
  (\\([1-7]?[0-7]|[1-3][0-7]{2})) {std::sscanf(yytext + 1, "%o", &(yylval->uint8)); return OCTAL_ESCAPE_SEQUENCE;}
  "'"                             {BEGIN(INITIAL); return SIMPLE_QUOTE;}
}
