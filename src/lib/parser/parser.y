%{

#include <iostream>
#include <comp/parser.h>
#include <comp/ast.h>
#include <memory>

union YYSTYPE;

void yyerror(void *scanner, comp::ast::RExpression *, const char *);
int yylex(YYSTYPE *lvalp, void *scanner);
void yy_scan_string(const char *str);

%}

%define api.pure full
%define parse.error verbose

%lex-param {void *scanner}

%parse-param {void *scanner}
%parse-param {comp::ast::RExpression *&root}

%union {
 uint8_t uint8;
 int32_t i;
 comp::ast::RExpression *e;
}

%token ADDITION_OPERATOR SUBTRACTION_OPERATOR MULTIPLICATION_OPERATOR DIVISION_OPERATOR REMAINDER_OPERATOR
%token SIMPLE_QUOTE CONTROL_CHAR_ESCAPE HEX_CHAR_ESCAPE

%token <i> INTEGER_LITERAL
%token <uint8> SOURCE_CHAR
%token <uint8> OCTAL_ESCAPE_SEQUENCE

%type <uint8> charAtom
%type <e> expression
%type <e> charLiteral
%type <e> root

%left SUBTRACTION_OPERATOR ADDITION_OPERATOR
%left MULTIPLICATION_OPERATOR DIVISION_OPERATOR
%left REMAINDER_OPERATOR

%%
root:
  expression {root = $1;};

charLiteral:
  SIMPLE_QUOTE charAtom SIMPLE_QUOTE {
    $$ = new comp::ast::Uint8Literal($2, nullptr);
  }

charAtom:
  SOURCE_CHAR {
    $$ = $1;
  }
  | OCTAL_ESCAPE_SEQUENCE {
    $$ = $1;
  }

expression:
  INTEGER_LITERAL {
    $$ = new comp::ast::Int64Literal($1, nullptr);
  }
  | charLiteral {
    $$ = $1;
  }
  | expression ADDITION_OPERATOR expression {
    std::shared_ptr<comp::ast::RExpression> left($1);
    std::shared_ptr<comp::ast::RExpression> right($3);
    $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Addition, left, right, nullptr);
  }
  | expression SUBTRACTION_OPERATOR expression {
    std::shared_ptr<comp::ast::RExpression> left($1);
    std::shared_ptr<comp::ast::RExpression> right($3);
    $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Subtraction, left, right, nullptr);
  }
  | expression MULTIPLICATION_OPERATOR expression {
    std::shared_ptr<comp::ast::RExpression> left($1);
    std::shared_ptr<comp::ast::RExpression> right($3);
    $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Multiplication, left, right, nullptr);
  }
  | expression DIVISION_OPERATOR expression {
    std::shared_ptr<comp::ast::RExpression> left($1);
    std::shared_ptr<comp::ast::RExpression> right($3);
    $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Division, left, right, nullptr);
  }
  | expression REMAINDER_OPERATOR expression {
    std::shared_ptr<comp::ast::RExpression> left($1);
    std::shared_ptr<comp::ast::RExpression> right($3);
    $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Remainder, left, right, nullptr);
  }
%%
