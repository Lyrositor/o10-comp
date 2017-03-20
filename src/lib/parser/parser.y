%{

#include <iostream>
#include <comp/parser.h>
#include <comp/ast.h>
#include <memory>

union YYSTYPE;

void yyerror(void *scanner, comp::ast::Expression *, const char *);
int yylex(YYSTYPE *lvalp, void *scanner);
void yy_scan_string(const char *str);

%}

%define api.pure full
%define parse.error verbose

%lex-param {void *scanner}

%parse-param {void *scanner}
%parse-param {comp::ast::Expression *&root}

%union {
 int32_t i;
 char * s;
 comp::ast::Expression *e;
 comp::ast::Program *program;
 comp::ast::Function *function;
 comp::ast::Identifier *identifier;
 comp::ast::Datatype *datatype;
 comp::ast::VarDecAffLitteral *varDecAffLitteral;
 comp::ast::SuiteDecAffLitteral *suiteDecAffLitteral;
 comp::ast::Datatype *datatype;
 comp::ast::Datatype *datatype;
 std::vector<comp::ast::Declaration> *declarationsList;
}

%token ADDITION_OPERATOR SUBTRACTION_OPERATOR MULTIPLICATION_OPERATOR DIVISION_OPERATOR REMAINDER_OPERATOR
%token <i> INTEGER_LITERAL
%type <e> expression
%type <e> root
%type <program> program
%type <function> function
%type <identifier> identifier
%type <declarationsList> declarationsList

%left SUBTRACTION_OPERATOR ADDITION_OPERATOR
%left MULTIPLICATION_OPERATOR DIVISION_OPERATOR
%left REMAINDER_OPERATOR

%%
root:
  expression {root = $1;};

/* Généralités */
program:
    declarationsList{
        std::shared_ptr<std::vector<comp::ast::Declaration>> body($1);
        $$ = new comp::ast::Program(body);
    }

declarationsList:
    declarationsList functionDec{
        std::shared_ptr<comp::ast::Function> decl($2);
        $1->push_back(decl);
        $$ = $1;
    }
    | declarationsList functionDef{
        std::shared_ptr<comp::ast::Function> def($2);
        $1->push_back(def);
        $$ = $1;
    }
    | declarationsList varDecAffLitteral ";"{
        std::shared_ptr<comp::ast::Function> decl($2);
        $$ = $1;
    }
    | {
        $$ = new std::vector<comp::ast::Declaration>();
    }

datatype:
    identifier{
        std::shared_ptr<std::vector<comp::ast::Identifier> name($1);
        $$ = new comp::ast::Datatype(name);
    }

/* Déclaration, affectation de variables */
varDecAffLitteral:
    varDecAffLitteral "," suiteDecAffLitteral {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        std::shared_ptr<comp::ast::VariableDeclarator> declarators($3);
        $$ = new comp::ast::VariableDeclaration(identifier, declarators);
    }
    | dataType suiteDecAffLitteral{
        std::shared_ptr<comp::ast::DataType> datatype($1);
        std::shared_ptr<comp::ast::VariableDeclarator> declarators($2);
        $$ = new comp::ast::VariableDeclaration(datatype, declarators);
    }

suiteDecAffLitteral:
    varIdentifierTabLiteral {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        $$ = new comp::ast::VariableDeclarator(identifier);
    }
    | identifier "=" literalExpr{
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        std::shared_ptr<comp::ast::Identifier> initial_value($3);
        $$ = new comp::ast::VariableDeclarator(identifier, initial_value);
    }

varDecAff:
    varDecAff "," suite {
        std::shared_ptr<comp::ast::VariableDeclaration> varDecAff($1);
        std::shared_ptr<comp::ast::VariableDeclarator> suite($3);
        $$ = new comp::ast::VariableDeclarator(varDecAff, suite);
    }
    | dataType suite {
        std::shared_ptr<comp::ast::DataType> datatype($1);
        std::shared_ptr<comp::ast::VariableDeclarator> suite($2);
        $$ = new comp::ast::VariableDeclarator(datatype, suite);
    }

suiteDecAff:
    varIdentifierTabLiteral {
        std::shared_ptr<comp::ast::VarDecAffLitteral> var($1);
        $$ = new comp::ast::VariableDeclarator(var);
    }
    | identifier "=" expr {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        std::shared_ptr<comp::ast::Expression> expr($3);
        $$ = new comp::ast::VariableDeclarator(identifier, expression);
    }

varAff:
    varIdentifier "=" expr{
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        std::shared_ptr<comp::ast::Expression> expr($3);
        $$ = new comp::ast::VariableDeclarator(identifier, expression);
    }

varUpdate:
    varIdentifier "++" {

    }
    | varIdentifier "--" {

    }
    | "++" varIdentifier {

    }
    | "--" varIdentifier{

    }

varIdentifier:
    identifier {
        std::shared_ptr<std::vector<comp::ast::Identifier> identifier($1);
        $$ = new comp::ast::Datatype(identifier, expression);
    }
    | identifier "[" expr "]"{
        std::shared_ptr<std::vector<comp::ast::Identifier> identifier($1);
        std::shared_ptr<std::vector<comp::ast::Expression> expression($3);
        $$ = new comp::ast::Datatype(identifier, expression);
    }

varIdentifierTabLiteral:
    identifier{
        std::shared_ptr<std::vector<comp::ast::Identifier> identifier($1);
        $$ = new comp::ast::Datatype(identifier);
    }
    | identifier "[" intLiteral "]"{
        std::shared_ptr<std::vector<comp::ast::Identifier> identifier($1);
        std::shared_ptr<std::vector<comp::ast::Expression> expression($3);
        $$ = new comp::ast::Datatype(identifier, expression);
    }

/* instructions */
instr:
    expr ";" {
        std::shared_ptr<comp::ast::Expression> expr($1);
        $$ = new comp::ast::ExpressionStatement(epxr);
    }
    | bloc {
        $$ = new comp::ast::BlockStatement();
    }
    | if {
        $$ = new comp::ast::IfStatement();
    }
    | while {
        $$ = new comp::ast::WhileStatement();
    }
    | for {
        $$ = new comp::ast::ForStatement();
    }
    | ";"{
    }

if_statement:
    "if" "(" expression ")" statement "else" statement {
        std::shared_ptr<comp::ast::Expression> test($3);
        std::shared_ptr<comp::ast::Statement> consequence($5);
        std::shared_ptr<comp::ast::Statement> alternative($7);
        $$ = new comp::ast::IfStatement(comp::ast::IfStatement::test, consequence, alternative);
    }
    | "if" "(" expression ")" statement {
        std::shared_ptr<comp::ast::Expression> test($3);
        std::shared_ptr<comp::ast::Statement> consequence($5);
        $$ = new comp::ast::IfStatement(comp::ast::IfStatement::test, consequence);
    }

while_statement:
    "while" "(" expr ")" instr {
        std::shared_ptr<comp::ast::Expression> expr($3);
        std::shared_ptr<comp::ast::Statement> body($5);
        $$ = new comp::ast::WhileStatement(expr, body);
    }

for_statement:
    "for" "("  exprOrVoid ";" exprOrVoid  ";" exprOrVoid ")" instr{
        std::shared_ptr<comp::ast::Expression> initialization($3);
        std::shared_ptr<comp::ast::Expression> condition($5);
        std::shared_ptr<comp::ast::Expression> iteration($7);
        std::shared_ptr<comp::ast::Expression> body($9);
        $$ = new comp::ast::ForStatement(initialization, condition, iteration, body);
    }

block_statement:
    "{" inside_block "}"{
        std::shared_ptr<comp::ast::BlockStatement> inside_block($2);
        $$ = new comp::ast::BlockStatement(inside_block);
    }

inside_block:
    insideBlock instr{
        std::shared_ptr<comp::ast::BlockStatement> inside_block($1);
        std::shared_ptr<comp::ast::Statement> instr($1);
        $$ = new comp::ast::BlockStatement(inside_block, instr);
    }
    | insideBlock varDec ";" {
        std::shared_ptr<comp::ast::BlockStatement> inside_block($1);
        std::shared_ptr<comp::ast::VariableDeclarator> varDec($2);
        $$ = new comp::ast::BlockStatement(inside_block, varDec);
    }
    | insideBlock return {
        std::shared_ptr<comp::ast::BlockStatement> inside_block($1);
        $$ = new comp::ast::BlockStatement(inside_block);
    }
    | {
        $$ = new comp::ast::BlockStatement();
    }

charLiteral:
    "'" char "'"{
        std::shared_ptr<comp::ast::Statement> char($2);
        $$ = new comp::ast::Literal(char);
    }

/* Déclaration, définition de fonctions */
paramsDec:
    paramsDef{
        std::shared_ptr<comp::ast::Identifier> paramsDef($1);
        $$ = new comp::ast::Parameter(paramsDef);
    }
    | datatype{
        std::shared_ptr<comp::ast::DataType> datatype($1);
        $$ = new comp::ast::Parameter(datatype);
    }
    | dataType "[""]"{
        std::shared_ptr<comp::ast::DataType> datatype($1);
        $$ = new comp::ast::Parameter(datatype);
    }

nonEmptyDecParametersList:
    nonEmptyDecParametersList "," paramsDec {

    }
    | paramsDec {

    }

decParametersList:
    nonEmptyDecParametersList{

    }
    | {

    }

paramsDef:
    dataType identifier {
        std::shared_ptr<comp::ast::DataType> datatype($1);
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        $$ = new comp::ast::Parameter(datatype, identifier);
    }
    | dataType identifier "[""]"{
        std::shared_ptr<comp::ast::DataType> datatype($1);
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        $$ = new comp::ast::Parameter(datatype, identifier);
    }


nonEmptyDefParametersList:
    nonEmptyDefParametersList "," paramsDef {

    }
    | paramsDef {

    }

defParametersList:
    nonEmptyDefParametersList {

    }
    | {

    }

functionDec:
    dataType identifier "(" decParametersList ")" ";"{
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        std::shared_ptr<comp::ast::Identifier> decParametersList($4);
        $$ = new comp::ast::Function(identifier, decParametersList);
    }

functionDef:
    dataType identifier "(" defParametersList ")" block{
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        std::shared_ptr<comp::ast::Identifier> defParametersList($4);
        std::shared_ptr<comp::ast::Block_Statement> block($6);
        $$ = new comp::ast::Function(identifier, decParametersList, block);
    }

return:
    "return" exprOrVoid ";"{
        std::shared_ptr<comp::ast::Identifier> expr($2);
        $$ = new comp::ast::ReturnStatement(expr);
    }

/* Expressions  */
LiteralExpr:
    intLiteral {
        std::shared_ptr<comp::ast::Int64Literal> int($1);
        $$ = new comp::ast::Expression(int);
    }
    | charLiteral {
        std::shared_ptr<comp::ast::Literal> char($1);
        $$ = new comp::ast::Expression(char);
    }

expression:
      LITTERAL_EXPRESSION {
        $$ = new comp::ast::Int64Literal($1, nullptr);
      }

      INTEGER_LITERAL {
        $$ = new comp::ast::Int64Literal($1, nullptr);
      }
      | expression ADDITION_OPERATOR expression {
        std::shared_ptr<comp::ast::Expression> left($1);
        std::shared_ptr<comp::ast::Expression> right($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Addition, left, right, nullptr);
      }
      | expression SUBTRACTION_OPERATOR expression {
        std::shared_ptr<comp::ast::Expression> left($1);
        std::shared_ptr<comp::ast::Expression> right($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Subtraction, left, right, nullptr);
      }
      | expression MULTIPLICATION_OPERATOR expression {
        std::shared_ptr<comp::ast::Expression> left($1);
        std::shared_ptr<comp::ast::Expression> right($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Multiplication, left, right, nullptr);
      }
      | expression DIVISION_OPERATOR expression {
        std::shared_ptr<comp::ast::Expression> left($1);
        std::shared_ptr<comp::ast::Expression> right($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Division, left, right, nullptr);
      }
      | expression REMAINDER_OPERATOR expression {
        std::shared_ptr<comp::ast::Expression> left($1);
        std::shared_ptr<comp::ast::Expression> right($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Remainder, left, right, nullptr);
      }

%%
