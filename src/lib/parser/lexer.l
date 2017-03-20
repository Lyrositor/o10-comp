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

/* charLiteral '([^\\'\n]|\\[abfnrtv\\'"?0]|\\[0-7]{1,3}|\\x[0-9a-e]{1,2})' */
intLiteral [0-9]+
identifier [a-zA-Z_$][a-zA-Z_$0-9]*


%%

[ \n\t]       {/* ignore */}
{intLiteral}  {yylval->i = atoi(yytext); return INTEGER_LITERAL;}
{identifier}  {yylval->s = yytext; return IDENTIFIER;}


";"           {return SEMICOLON;}
"["           {return OPEN_BRACKET;}
"]"           {return CLOSE_BRACKET;}
"++"          {return INCREMENT_OPERATOR;}
"--"          {return DECREMENT_OPERATOR;}
"("           {return OPEN_PAREN;}
")"           {return CLOSE_PAREN;}
"if"          {return IF;}
"else"        {return ELSE;}
"while"       {return WHILE;}
"for"         {return FOR;}
"return"      {return RETURN;}
"{"           {return OPEN_BRACE;}
"}"           {return CLOSE_BRACE;}

"="           {return SIMPLE_ASSIGNMENT_OPERATOR;}
","           {return COMMA_OPERATOR;}
"=="          {return EQUALS_OPERATOR;}
"!="          {return NOT_EQUAL_OPERATOR;}
"<"           {return LESS_THAN_OPERATOR;}
"<="          {return LESS_THAN_OR_EQUAL_OPERATOR;}
">"           {return GREATER_THAN_OPERATOR;}
">="          {return GREATER_THAN_OR_EQUAL_OPERATOR;}
"<<"          {return LEFT_SHIFT_OPERATOR;}
">>"          {return RIGHT_SHIFT_OPERATOR;}
"+"           {return ADDITION_OPERATOR;}
"-"           {return SUBTRACTION_OPERATOR;}
"/"           {return DIVISION_OPERATOR;}
"*"           {return MULTIPLICATION_OPERATOR;}
"%"           {return REMAINDER_OPERATOR;}
"+="          {return ADD_ASSIGN_OPERATOR;}
"-="          {return MINUS_ASSIGN_OPERATOR;}
"*="          {return MULTP_ASSIGN_OPERATOR;}
"/="          {return DIV_ASSIGN_OPERATOR;}
"%="          {return REM_ASSIGN_OPERATOR;}
"<<="         {return LEFT_SHIFT_ASSIGN_OPERATOR;}
">>="         {return RIGHT_SHIFT_ASSIGN_OPERATOR;}
"&="          {return AND_ASSIGN_OPERATOR;}
"^="          {return XOR_ASSIGN_OPERATOR;}
"|="          {return OR_ASSIGN_OPERATOR;}
"|"           {return BINARY_OR_OPERATOR;}
"&"           {return BINARY_AND_OPERATOR;}
"^"           {return BINARY_XOR_OPERATOR;}
"||"          {return OR_OPERATOR;}
"&&"          {return AND_OPERATOR;}
"!"           {return NOT_OPERATOR;}
"~"           {return BINARY_ONES_COMPLEMENT_OPERATOR;}

<INITIAL>"'"                      {BEGIN(charLiteral); return SIMPLE_QUOTE;}
<charLiteral>{
  [^\\'\n]                        {yylval->uint8 = yytext[0]; return SOURCE_CHAR;}
  (\\([1-7]?[0-7]|[1-3][0-7]{2})) {std::sscanf(yytext + 1, "%o", &(yylval->uint8)); return OCTAL_ESCAPE_SEQUENCE;}
  (\\x[1-9a-fA-F]?[0-9a-fA-F])    {std::sscanf(yytext + 2, "%x", &(yylval->uint8)); return HEX_ESCAPE_SEQUENCE;}
  "\\a"                           {yylval->uint8 = 0x07; return SOURCE_CHAR;}
  "\\b"                           {yylval->uint8 = 0x08; return SOURCE_CHAR;}
  "\\f"                           {yylval->uint8 = 0x0c; return SOURCE_CHAR;}
  "\\n"                           {yylval->uint8 = 0x0a; return SOURCE_CHAR;}
  "\\r"                           {yylval->uint8 = 0x0d; return SOURCE_CHAR;}
  "\\t"                           {yylval->uint8 = 0x09; return SOURCE_CHAR;}
  "\\v"                           {yylval->uint8 = 0x0b; return SOURCE_CHAR;}
  "\\\'"                          {yylval->uint8 = 0x27; return SOURCE_CHAR;}
  "\\\""                          {yylval->uint8 = 0x22; return SOURCE_CHAR;}
  "\\?"                           {yylval->uint8 = 0x3f; return SOURCE_CHAR;}
  "\\"                            {yylval->uint8 = 0x5c; return SOURCE_CHAR;}
  "'"                             {BEGIN(INITIAL); return SIMPLE_QUOTE;}
}
