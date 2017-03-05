%{

#include <stdio.h>
#include <comp/parser.h>
#include <comp/ast.h>
#include <memory>

void yyerror(comp::ast::Expression *, const char *);
int yylex(void);
void yy_scan_string(const char *str);

%}
%union {
 int32_t i;
 comp::ast::Expression *e;
}
%token ADDITION_OPERATOR SUBTRACTION_OPERATOR MULTIPLICATION_OPERATOR DIVISION_OPERATOR REMAINDER_OPERATOR
%token <i> INTEGER_LITERAL
%type <e> expression
%type <e> root

%left SUBTRACTION_OPERATOR ADDITION_OPERATOR
%left MULTIPLICATION_OPERATOR DIVISION_OPERATOR
%left REMAINDER_OPERATOR

%parse-param {comp::ast::Expression *&root}

%%
root:
  expression {root = $1;};

expression:
  INTEGER_LITERAL {$$ = new comp::ast::Literal($1, nullptr);}
  | expression ADDITION_OPERATOR expression {$$ = new comp::ast::BinaryExpression(comp::ast::AdditionOperator, std::shared_ptr<comp::ast::Expression>($1), std::shared_ptr<comp::ast::Expression>($3), nullptr);}
  | expression SUBTRACTION_OPERATOR expression {$$ = new comp::ast::BinaryExpression(comp::ast::SubtractionOperator, std::shared_ptr<comp::ast::Expression>($1), std::shared_ptr<comp::ast::Expression>($3), nullptr);}
  | expression MULTIPLICATION_OPERATOR expression {$$ = new comp::ast::BinaryExpression(comp::ast::MultiplicationOperator, std::shared_ptr<comp::ast::Expression>($1), std::shared_ptr<comp::ast::Expression>($3), nullptr);}
  | expression DIVISION_OPERATOR expression {$$ = new comp::ast::BinaryExpression(comp::ast::DivisionOperator, std::shared_ptr<comp::ast::Expression>($1), std::shared_ptr<comp::ast::Expression>($3), nullptr);}
  | expression REMAINDER_OPERATOR expression {$$ = new comp::ast::BinaryExpression(comp::ast::RemainderOperator, std::shared_ptr<comp::ast::Expression>($1), std::shared_ptr<comp::ast::Expression>($3), nullptr);}
%%


void yyerror(comp::ast::Expression * res, const char * msg) {
   printf("Syntax error : %s\n",msg);
}

namespace comp {
  namespace parser {
    std::shared_ptr<comp::ast::Expression> parse(){
      comp::ast::Expression *root = nullptr;
      yy_scan_string("123+456");
      yyparse(root);
      return std::shared_ptr<comp::ast::Expression>(root);
    }
  }
}
