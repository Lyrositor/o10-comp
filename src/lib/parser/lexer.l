%{
#include <cstdio>
#include <stdlib.h>
#include <comp/ast.h>
#include <comp/exceptions.h>
#include <comp/parser/parser_config.h>

// Generated with bison by CMake (parser.tab.hpp is in the build directory)
#include "parser.tab.hpp"

#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line; \
    yylloc->first_column = yylloc->last_column; \
    yylloc->first_index = yylloc->last_index; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
        if(yytext[i] == '\n') { \
            yylloc->last_line++; \
            yylloc->last_column = 0; \
            yylloc->last_index++; \
        } \
        else { \
            yylloc->last_column++; \
            yylloc->last_index++; \
        } \
    }

%}
%option 8bit
%option bison-bridge
%option pointer
/* %option nodefault */
%option noinput
%option nounput
%option noyywrap
%option reentrant
%option warn
%option bison-locations

%x charLiteral
%%
[ \n\t]       {/* ignore */}
";"           {return SEMICOLON;}
"["           {return OPEN_BRACKET;}
"]"           {return CLOSE_BRACKET;}
"("           {return OPEN_PAREN;}
")"           {return CLOSE_PAREN;}
"if"          {return IF;}
"else"        {return ELSE;}
"while"       {return WHILE;}
"for"         {return FOR;}
"return"      {return RETURN;}
"{"           {return OPEN_BRACE;}
"}"           {return CLOSE_BRACE;}
"!="          {return NOT_EQUAL_OPERATOR;}
"!"           {return NOT_OPERATOR;}
"<<="         {return LEFT_SHIFT_ASSIGN_OPERATOR;}
"<="          {return LESS_THAN_OR_EQUAL_OPERATOR;}
"<<"          {return LEFT_SHIFT_OPERATOR;}
"<"           {return LESS_THAN_OPERATOR;}
">>="         {return RIGHT_SHIFT_ASSIGN_OPERATOR;}
">="          {return GREATER_THAN_OR_EQUAL_OPERATOR;}
">>"          {return RIGHT_SHIFT_OPERATOR;}
">"           {return GREATER_THAN_OPERATOR;}
"+="          {return ADD_ASSIGN_OPERATOR;}
"++"          {return INCREMENT_OPERATOR;}
"+"           {return ADDITION_OPERATOR;}
"-="          {return MINUS_ASSIGN_OPERATOR;}
"--"          {return DECREMENT_OPERATOR;}
"-"           {return SUBTRACTION_OPERATOR;}
"*="          {return MULTP_ASSIGN_OPERATOR;}
"*"           {return MULTIPLICATION_OPERATOR;}
"/="          {return DIV_ASSIGN_OPERATOR;}
"/"           {return DIVISION_OPERATOR;}
"%="          {return REM_ASSIGN_OPERATOR;}
"%"           {return REMAINDER_OPERATOR;}
"&="          {return AND_ASSIGN_OPERATOR;}
"&&"          {return AND_OPERATOR;}
"&"           {return BINARY_AND_OPERATOR;}
"^="          {return XOR_ASSIGN_OPERATOR;}
"^"           {return BINARY_XOR_OPERATOR;}
"|="          {return OR_ASSIGN_OPERATOR;}
"||"          {return OR_OPERATOR;}
"|"           {return BINARY_OR_OPERATOR;}
"=="          {return EQUALS_OPERATOR;}
"="           {return SIMPLE_ASSIGNMENT_OPERATOR;}
","           {return COMMA_OPERATOR;}
"~"           {return BINARY_ONES_COMPLEMENT_OPERATOR;}
"?"                               {return QUESTION_MARK;}
":"                               {return COLON;}
"char"                            {return CHAR_TYPE;}
"int32_t"                         {return INT32_TYPE;}
"int64_t"                         {return INT64_TYPE;}
"void"                            {return VOID_TYPE;}

<INITIAL>"'"                      {BEGIN(charLiteral); return SIMPLE_QUOTE;}
<charLiteral>{
  [^\\'\n]                        {yylval->uint8 = yytext[0]; return CHAR_ATOM;}
  (\\([1-7]?[0-7]|[1-3][0-7]{2})) {std::sscanf(yytext + 1, "%o", &(yylval->uint8)); return CHAR_ATOM;}
  (\\x[1-9a-fA-F]?[0-9a-fA-F])    {std::sscanf(yytext + 2, "%x", &(yylval->uint8)); return CHAR_ATOM;}
  "\\a"                           {yylval->uint8 = 0x07; return CHAR_ATOM;}
  "\\b"                           {yylval->uint8 = 0x08; return CHAR_ATOM;}
  "\\f"                           {yylval->uint8 = 0x0c; return CHAR_ATOM;}
  "\\n"                           {yylval->uint8 = 0x0a; return CHAR_ATOM;}
  "\\r"                           {yylval->uint8 = 0x0d; return CHAR_ATOM;}
  "\\t"                           {yylval->uint8 = 0x09; return CHAR_ATOM;}
  "\\v"                           {yylval->uint8 = 0x0b; return CHAR_ATOM;}
  "\\\'"                          {yylval->uint8 = 0x27; return CHAR_ATOM;}
  "\\\""                          {yylval->uint8 = 0x22; return CHAR_ATOM;}
  "\\?"                           {yylval->uint8 = 0x3f; return CHAR_ATOM;}
  "\\\\"                          {yylval->uint8 = 0x5c; return CHAR_ATOM;}
  "'"                             {BEGIN(INITIAL); return SIMPLE_QUOTE;}
}
([0-9]+)                          {yylval->int64 = atoi(yytext); return INTEGER_LITERAL;}
([a-zA-Z_$][a-zA-Z_$0-9]*)        {yylval->cstring = yytext; return IDENTIFIER;}

.                                 {throw comp::UnexpectedTokenError(yytext, LOCATION(yylloc));}
