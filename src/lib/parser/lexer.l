%{

#include <stdio.h>
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

charLiteral '([^\\'\n]|\\[abfnrtv\\'"?0]|\\[0-7]{1,3}|\\x[0-9a-e]{1,2})'
intLiteral [0-9]+
identifier [a-zA-Z_$][a-zA-Z_$0-9]*

%%

[ \n\t]       {/* ignore */}
{intLiteral}  {yylval->i = atoi(yytext); return INTEGER_LITERAL;}
{identifier}  {yylval->s = yytext; return IDENTIFIER;}

";"           {return SEMICOLON;}
"["           {return OPEN_BRACKET;}
"]"           {return CLOSE_BRACKET;}
"++"          {return PLUS_PLUS;}
"--"          {return MINUS_MINUS;}
"("           {return OPEN_PAREN;}
")"           {return CLOSE_PAREN;}
"if"          {return IF;}
"else"        {return ELSE;}
"while"       {return WHILE;}
"for"         {return FOR;}
"return"      {return RETURN;}
"{"           {return OPEN_CURLY_BRACKET;}
"}"           {return CLOSE_CURLY_BRACKET;}

"="           {return EQUAL_OPERATOR;}
","           {return COMMA_OPERATOR;}
"=="          {return EQUAL_EQUAL_OPERATOR;}
"!="          {return NO_EQUAL_OPERATOR;}
"<"           {return LESS_THAN_OPERATOR;}
"<="          {return NOT_MORE_THAN_OPERATOR;}
">"           {return MORE_THAN_OPERATOR;}
">="          {return NOT_LESS_THAN_OPERATOR;}
"<<"          {return LEFT_SHIFT_OPERATOR;}
">>"          {return RIGHT_SHIFT_OPERATOR;}
"+"           {return ADDITION_OPERATOR;}
"-"           {return SUBTRACTION_OPERATOR;}
"/"           {return DIVISION_OPERATOR;}
"*"           {return MULTIPLICATION_OPERATOR;}
"%"           {return REMAINDER_OPERATOR;}
"+="          {return ADD_EQUAL_OPERATOR;}
"-="          {return MINUS_EQUAL_OPERATOR;}
"*="          {return MULTP_EQUAL_OPERATOR;}
"/="          {return DIV_EQUAL_OPERATOR;}
"%="          {return REM_EQUAL_OPERATOR;}
"<<="         {return LEFT_SHIFT_EQUAL_OPERATOR;}
">>="         {return RIGHT_SHIFT_EQUAL_OPERATOR;}
"&="          {return AND_EQUAL_OPERATOR;}
"^="          {return XOR_EQUAL_OPERATOR;}
"|="          {return OR_EQUAL_OPERATOR;}
"|"           {return BINARY_OR_OPERATOR;}
"&"           {return BINARY_AND_OPERATOR;}
"^"           {return BINARY_XOR_OPERATOR;}
"||"          {return OR_OPERATOR;}
"&&"          {return AND_OPERATOR;}
"!"           {return NOT_OPERATOR;}
"~"           {return BINARY_ONES_COMPLEMENT_OPERATOR;}

