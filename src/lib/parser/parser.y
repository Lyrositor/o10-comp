%{

#include <iostream>
#include <comp/parser.h>
#include <comp/ast.h>
#include <memory>

union YYSTYPE;

void yyerror(void *scanner, comp::ast::Program *, const char *);
int yylex(YYSTYPE *lvalp, void *scanner);
void yy_scan_string(const char *str);

%}

%define api.pure full
%define parse.error verbose

%lex-param {void *scanner}

%parse-param {void *scanner}
%parse-param {comp::ast::Program *&root}

%union {
  /* Tokens */
  uint8_t uint8;
  int64_t int64;
  char * cstring;
  /* AST nodes */
  comp::ast::ArrayDeclarator *arrayDeclarator;
  comp::ast::BlockStatement *blockStatement;
  comp::ast::CallExpression *callExpression;
  comp::ast::DataType *dataType;
  comp::ast::Declarator *declarator;
  comp::ast::Function *function;
  comp::ast::Identifier *identifier;
  comp::ast::LExpression *lExpression;
  comp::ast::IdentifierDataType *identifierDataType;
  comp::ast::Program *program;
  comp::ast::RExpression *rExpression;
  comp::ast::Statement *statement;
  comp::ast::Parameter *parameter;
  comp::ast::VariableDeclaration *variableDeclaration;
  comp::ast::VariableDeclarator *variableDeclarator;
  /* Temporary vectors */
  std::vector<std::shared_ptr<comp::ast::Declaration>> *declarationsList;
  std::vector<std::shared_ptr<comp::ast::Parameter>> *parametersList;
  std::vector<std::shared_ptr<comp::ast::VariableDeclarator>> *variableDeclaratorsList;
}

/* Untyped tokens */
%token ADDITIONASSIGNMENT_OPERATOR BITWISEANDASSIGNMENT_OPERATOR BITWISEORASSIGNMENT_OPERATOR BITWISEXORASSIGNMENT_OPERATOR
%token DIVISIONASSIGNMENT_OPERATOR EQUALITY_OPERATOR EXPONENTIATIONASSIGNMENT_OPERATOR EXPONENTIATION_OPERATOR IDENTITY_OPERATOR
%token INEQUALITY_OPERATOR LEFTSHIFTASSIGNMENT_OPERATOR LEFTSHIFT_OPERATOR LITTERAL_EXPRESSION MULTIPLICATIONASSIGNMENT_OPERATOR
%token NONIDENTITY_OPERATOR REMAINDREASSIGNMENT_OPERATOR RIGHTSHIFTASSIGNMENT_OPERATOR RIGHTSHIFT_OPERATOR SUBSTRACTIONASSIGNMENT_OPERATOR
%token EQUAL_OPERATOR GREATERTHAN_OPERATOR GREATERTHANOREQUAL_OPERATOR LESSERTHAN_OPERATOR LESSERTHANOREQUAL_OPERATOR
%token EQUALEQUAL_OPERATOR LOGICALAND_OPERATOR LOGICALOR_OPERATOR LOGICALNOT_OPERATOR XOR_OPERATOR UNARYNEGATION_OPERATOR UNARYPLUS_OPERATOR
%token SEMICOLON OPEN_BRACKET CLOSE_BRACKET INCREMENT_OPERATOR DECREMENT_OPERATOR OPEN_PAREN CLOSE_PAREN
%token SUBSTRACTION_OPERATOR COMMA_OPERATOR_OPERATOR
%token IF ELSE WHILE FOR RETURN OPEN_BRACE CLOSE_BRACE
%token SIMPLE_ASSIGNMENT_OPERATOR COMMA_OPERATOR EQUALS_OPERATOR NOT_EQUAL_OPERATOR
%token LESS_THAN_OPERATOR LESS_THAN_OR_EQUAL_OPERATOR GREATER_THAN_OPERATOR GREATER_THAN_OR_EQUAL_OPERATOR
%token LEFT_SHIFT_OPERATOR RIGHT_SHIFT_OPERATOR
%token ADDITION_OPERATOR SUBTRACTION_OPERATOR DIVISION_OPERATOR MULTIPLICATION_OPERATOR REMAINDER_OPERATOR
%token ADD_ASSIGN_OPERATOR MINUS_ASSIGN_OPERATOR MULTP_ASSIGN_OPERATOR DIV_ASSIGN_OPERATOR REM_ASSIGN_OPERATOR
%token LEFT_SHIFT_ASSIGN_OPERATOR RIGHT_SHIFT_ASSIGN_OPERATOR AND_ASSIGN_OPERATOR XOR_ASSIGN_OPERATOR OR_ASSIGN_OPERATOR
%token BINARY_OR_OPERATOR BINARY_AND_OPERATOR BINARY_XOR_OPERATOR
%token OR_OPERATOR AND_OPERATOR NOT_OPERATOR BINARY_ONES_COMPLEMENT_OPERATOR
%token SIMPLE_QUOTE
%token CHAR_TYPE INT32_TYPE INT64_TYPE VOID_TYPE

/* Typed tokens */
%token <uint8> CHAR_ATOM
%token <int64> INTEGER_LITERAL
%token <cstring> IDENTIFIER

/* AST nodes */ /*
%type <arrayDeclarator>
%type <blockStatement>
%type <callExpression> */
%type <dataType> arrayDataType dataType
%type <declarator> declarator
%type <function> functionDeclaration
%type <identifier> identifier /*
%type <lExpression> */
%type <identifierDataType> identifierDataType
%type <program> program root /*
%type <rExpression> charLiteral
%type <statement> */
%type <parameter> parameter
%type <variableDeclaration> variableDeclaration
%type <variableDeclarator> variableDeclarator

/* Temporary vectors */
%type <declarationsList> declarationsList
%type <parametersList> parametersList
%type <variableDeclaratorsList> variableDeclaratorsList

/*

%type <declarationsList>
%type <parametersList>  functionCallParams
%type <variableDeclaratorsList> variableDeclaratorsList
%type <unaryExpression> unaryExpression varUpdate
%type <dataType> dataType
%type <declarator>
%type <identifierDataType> identifierDataType  literalExpr
%type <arrayDataType> arrayDataType
%type <parameter> parameter
%type <statement> statement
%type <expressionStatement> expressionStatement
%type <ifStatement> ifStatement
%type <whileStatement> whileStatement
%type <forStatement> forStatement
%type <block_statement> insideBlock block
%type <returnStatement> returnStatement
%type <lvalue> LValue
%type <callExpression> functionCall

%left SUBTRACTION_OPERATOR ADDITION_OPERATOR
%left MULTIPLICATION_OPERATOR DIVISION_OPERATOR
%left REMAINDER_OPERATOR

*/

%%
root:
  program {
    root = $1;
  }

program:
  declarationsList {
    std::vector<std::shared_ptr<comp::ast::Declaration>> body(*$1);
    delete $1;
    $$ = new comp::ast::Program(body);
  }

declarationsList:
  declarationsList functionDeclaration {
    std::shared_ptr<comp::ast::Declaration> function_declaration($2);
    $1->push_back(function_declaration);
    $$ = $1;
  }
/*
  | declarationsList functionDefinition {
    std::shared_ptr<comp::ast::Function> functionDefinition($2);
    $1->push_back(functionDefinition);
    $$ = $1;
  }
*/
  | declarationsList variableDeclaration {
    std::shared_ptr<comp::ast::Declaration> function_declaration($2);
    $1->push_back(function_declaration);
    $$ = $1;
  }
  | {
    $$ = new std::vector<std::shared_ptr<comp::ast::Declaration>>();
  }

functionDeclaration:
  identifierDataType identifier OPEN_PAREN parametersList CLOSE_PAREN SEMICOLON {
    std::shared_ptr<comp::ast::DataType> return_type($1);
    std::shared_ptr<comp::ast::Identifier> identifier($2);
    std::vector<std::shared_ptr<comp::ast::Parameter>> parameters(*$4);
    delete $4;
    $$ = new comp::ast::Function(identifier, parameters, return_type, nullptr);
  }
  | identifierDataType identifier OPEN_PAREN CLOSE_PAREN SEMICOLON {
    std::shared_ptr<comp::ast::DataType> return_type($1);
    std::shared_ptr<comp::ast::Identifier> identifier($2);
    $$ = new comp::ast::Function(identifier, {}, return_type, nullptr);
  }

dataType:
  identifierDataType {
    $$ = $1;
  }
  | arrayDataType {
    $$ = $1;
  }

identifierDataType:
  CHAR_TYPE {
    $$ = new comp::ast::IdentifierDataType(comp::ast::Identifier::Create("char"));
  }
  | INT32_TYPE {
    $$ = new comp::ast::IdentifierDataType(comp::ast::Identifier::Create("int32_t"));
  }
  | INT64_TYPE {
    $$ = new comp::ast::IdentifierDataType(comp::ast::Identifier::Create("int64_t"));
  }
  | VOID_TYPE {
    $$ = new comp::ast::IdentifierDataType(comp::ast::Identifier::Create("void"));
  }

arrayDataType:
  identifierDataType OPEN_BRACKET CLOSE_BRACKET{
    std::shared_ptr<comp::ast::DataType> item_type($1);
    $$ = new comp::ast::ArrayDataType(item_type, nullptr);
  }

identifier:
  IDENTIFIER {
    $$ = new comp::ast::Identifier($1);
  }

parametersList:
  parametersList COMMA_OPERATOR parameter {
    std::shared_ptr<comp::ast::Parameter> parameter($3);
    $1->push_back(parameter);
    $$ = $1;
  }
  | parameter {
    std::shared_ptr<comp::ast::Parameter> parameter($1);
    $$ = new std::vector<std::shared_ptr<comp::ast::Parameter>>();
    $$->push_back(parameter);
  }

parameter:
  identifierDataType declarator {
    std::shared_ptr<comp::ast::IdentifierDataType> literal_data_type($1);
    std::shared_ptr<comp::ast::Declarator> declarator($2);
    $$ = new comp::ast::NamedParameter(literal_data_type, declarator);
  }
  | dataType {
    std::shared_ptr<comp::ast::DataType> dataType($1);
    $$ = new comp::ast::AnonymousParameter(dataType);
  }

declarator:
  identifier {
    std::shared_ptr<comp::ast::Identifier> identifier($1);
    $$ = new comp::ast::IdentifierDeclarator(identifier);
  }
/*  | identifier OPEN_BRACKET CLOSE_BRACKET {
    std::shared_ptr<comp::ast::Identifier> declarator($1);
    $$ = new comp::ast::ArrayDeclarator(declarator, nullptr);
  }
  | identifier OPEN_BRACKET expression CLOSE_BRACKET {
    std::shared_ptr<comp::ast::Identifier> declarator($1);
    std::shared_ptr<comp::ast::Expression> size($3);
    $$ = new comp::ast::ArrayDeclarator(declarator, size);
  }
*/

/*
functionDefinition:
    dataType identifier OPEN_PAREN parametersList CLOSE_PAREN block {
        std::shared_ptr<comp::ast::DataType> dataType($1);
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        std::shared_ptr<comp::ast::Parameter> parametersList($4);
        std::shared_ptr<comp::ast::BlockStatement> block($6);
        $$ = new comp::ast::Function(dataType, identifier, parametersList, block);
    }
*/

variableDeclaration:
  identifierDataType variableDeclaratorsList SEMICOLON {
    std::shared_ptr<comp::ast::IdentifierDataType> base_type($1);
    std::vector<std::shared_ptr<comp::ast::VariableDeclarator>> declarators(*$2);
    delete $2;
    $$ = new comp::ast::VariableDeclaration(base_type, declarators);
  }

variableDeclaratorsList:
  variableDeclaratorsList COMMA_OPERATOR variableDeclarator {
    std::shared_ptr<comp::ast::VariableDeclarator> variable_declarator($3);
    $1->push_back(variable_declarator);
    $$ = $1;
  }
  | variableDeclarator {
    std::shared_ptr<comp::ast::VariableDeclarator> variable_declarator($1);
    $$ = new std::vector<std::shared_ptr<comp::ast::VariableDeclarator>>;
    $$->push_back(variable_declarator);
  }

variableDeclarator:
  declarator {
      std::shared_ptr<comp::ast::Declarator> declarator($1);
      $$ = new comp::ast::VariableDeclarator(declarator, nullptr);
  }
/*
  | declarator EQUAL_OPERATOR declarator {
      std::shared_ptr<comp::ast::Declarator> decl1($1);
      std::shared_ptr<comp::ast::Declarator> decl2($3);
      $$ = new comp::ast::VariableDeclarator(decl1, decl2);
  }
*/

/*
LValue:
    identifier {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        $$ = new comp::ast::LExpression(identifier);
    }
    | identifier OPEN_BRACE expr CLOSE_BRACKET {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        std::shared_ptr<comp::ast::Expression> expr($3);
        $$ = new comp::ast::LExpression(identifier, expr);
    }
    | functionCall OPEN_BRACKET expr CLOSE_BRACKET {
        std::shared_ptr<comp::ast::CallExpression> functionCall($1);
        std::shared_ptr<comp::ast::Expression> expr($3);
        $$ = new comp::ast::LExpression(functionCall, expr);
    }

varUpdate:
    LValue INCREMENT_OPERATOR {
        std::shared_ptr<comp::ast::Identifier> LValue($1);
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::PostfixIncrement;
        $$ = new comp::ast::UnaryExpression(op, LValue);
    }
    | LValue DECREMENT_OPERATOR {
        std::shared_ptr<comp::ast::Identifier> LValue($1);
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::PostfixDecrement;
        $$ = new comp::ast::UnaryExpression(op, LValue);
    }
    | INCREMENT_OPERATOR LValue {
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::PrefixIncrement;
        std::shared_ptr<comp::ast::Identifier> LValue($2);
        $$ = new comp::ast::UnaryExpression(op, LValue);
    }
    | DECREMENT_OPERATOR LValue{
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::PrefixDecrement;
        std::shared_ptr<comp::ast::Identifier> LValue($2);
        $$ = new comp::ast::UnaryExpression(op, LValue);
    }

functionCall:
    identifier OPEN_PAREN functionCallParams CLOSE_PAREN {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        std::vector<std::shared_ptr<comp::ast::Parameter>> functionCallParams($3);
        $$ = new comp::ast::CallExpression(identifier, functionCallParams);
    }
    | identifier OPEN_PAREN CLOSE_PAREN {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        $$ = new comp::ast::CallExpression(identifier);
    }

functionCallParams:
    functionCallParams COMMA_OPERATOR expr {
        std::vector<std::shared_ptr<comp::ast::Parameter>> functionCallParams($1);
        std::shared_ptr<comp::ast::Expression> expr($3);
        $$ = new comp::ast::Parameter(functionCallParams, expr);
    }
    | expr {
        std::shared_ptr<comp::ast::Expression> expr($1);
        $$ = new comp::ast::Parameter(expr);
    }

statement:
    expressionStatement {
        std::shared_ptr<comp::ast::ExpressionStatement> expressionStatement($1);
        $$ = new comp::ast::Statement(expressionStatement);
    }
    | returnStatement {
        std::shared_ptr<comp::ast::ReturnStatement> returnStatement($1);
        $$ = new comp::ast::Statement(returnStatement);
    }
    | block {
        std::shared_ptr<comp::ast::BlockStatement> block($1);
        $$ = new comp::ast::Statement(block);
    }
    | ifStatement {
        std::shared_ptr<comp::ast::IfStatement> ifStatement($1);
        $$ = new comp::ast::Statement(ifStatement);
    }
    | whileStatement {
        std::shared_ptr<comp::ast::WhileStatement> whileStatement($1);
        $$ = new comp::ast::Statement(whileStatement);
    }
    | forStatement {
        std::shared_ptr<comp::ast::ForStatement> forStatement($1);
        $$ = new comp::ast::Statement(forStatement);
    }
    | SEMICOLON{
        $$ = new comp::ast::Statement();
    }

expressionStatement:
    expr SEMICOLON{
        std::shared_ptr<comp::ast::Expression> expr($1);
        $$ = new comp::ast::ExpressionStatement(expr);
    }

returnStatement:
    RETURN expressionOrVoid SEMICOLON {
        std::shared_ptr<comp::ast::Identifier> expr($2);
        $$ = new comp::ast::ReturnStatement(expr);
    }
    | RETURN SEMICOLON {
        $$ = new comp::ast::ReturnStatement();
    }

ifStatement:
    IF OPEN_PAREN expr CLOSE_PAREN statement ELSE statement {
        std::shared_ptr<comp::ast::RExpression> test($3);
        std::shared_ptr<comp::ast::Statement> consequence($5);
        std::shared_ptr<comp::ast::Statement> alternative($7);
        $$ = new comp::ast::IfStatement(comp::ast::IfStatement::test, consequence, alternative);
    }
    | IF OPEN_PAREN expr CLOSE_PAREN statement {
        std::shared_ptr<comp::ast::RExpression> expr($3);
        std::shared_ptr<comp::ast::Statement> consequence($5);
        $$ = new comp::ast::IfStatement(comp::ast::IfStatement::test, consequence);
    }

whileStatement:
    WHILE OPEN_PAREN expr CLOSE_PAREN statement {
        std::shared_ptr<comp::ast::RExpression> expr($3);
        std::shared_ptr<comp::ast::Statement> statement($5);
        $$ = new comp::ast::WhileStatement(expr, statement);
    }

forStatement:
    FOR OPEN_PAREN expressionOrVoid SEMICOLON expressionOrVoid SEMICOLON expressionOrVoid CLOSE_PAREN statement {
        std::shared_ptr<comp::ast::RExpression> initialization($3);
        std::shared_ptr<comp::ast::RExpression> condition($5);
        std::shared_ptr<comp::ast::RExpression> iteration($7);
        std::shared_ptr<comp::ast::Statement> body($9);
        $$ = new comp::ast::ForStatement(initialization, condition, iteration, body);
    }
    | FOR OPEN_PAREN variableDeclaration expressionOrVoid SEMICOLON expressionOrVoid CLOSE_PAREN statement {
        std::shared_ptr<comp::ast::VariableDeclaration> initialization($3);
        std::shared_ptr<comp::ast::RExpression> condition($4);
        std::shared_ptr<comp::ast::RExpression> iteration($6);
        std::shared_ptr<comp::ast::Statement> body($8);
        $$ = new comp::ast::ForStatement(initialization, condition, iteration, body);
    }

block:
    OPEN_BRACE insideBlock CLOSE_BRACE {
        std::shared_ptr<comp::ast::BlockStatement> insideBlock($2);
        $$ = new comp::ast::BlockStatement(insideBlock);
    }
    | OPEN_BRACE CLOSE_BRACE {
        $$ = new comp::ast::BlockStatement();
    }

insideBlock:
    insideBlock statement {
        std::shared_ptr<comp::ast::BlockStatement> insideBlock($1);
        std::shared_ptr<comp::ast::Statement> statement($2);
        $$ = new comp::ast::BlockStatement(insideBlock, instr);
    }
    | insideBlock variableDeclaration {
        std::shared_ptr<comp::ast::BlockStatement> insideBlock($1);
        std::shared_ptr<comp::ast::VariableDeclaration> variableDeclaration($2);
        $$ = new comp::ast::BlockStatement(insideBlock, variableDeclaration);
    }

expressionOrVoid:
    expr{
        std::shared_ptr<comp::ast::RExpression> expr($1);
        $$ = new comp::ast::RExpression(expr);
    }
    | {
        $$ = new comp::ast::RExpression();
    }

literalExpr:
    INTEGER_LITERAL {
        std::shared_ptr<comp::ast::Int64Literal> int($1);
        $$ = new comp::ast::RExpression(int);
    }
    | charLiteral {
        std::shared_ptr<comp::ast::Literal> char($1);
        $$ = new comp::ast::Uint8Literal(char, nullptr);
    }
    | hexIntegerLiteral {
        std::shared_ptr<comp::ast::Literal> hex($1);
        $$ = new comp::ast::RExpression(hex);
    }

charLiteral:
    SIMPLE_QUOTE CHAR_ATOM SIMPLE_QUOTE {
        $$ = new comp::ast::Uint8Literal($2, nullptr);
    }

expr:
    expr op expr{
        std::shared_ptr<comp::ast::RExpression> expr1($1);
        std::shared_ptr<comp::ast::BinaryOperator> op($2);
        std::shared_ptr<comp::ast::RExpression> expr2($3);
        $$ = new comp::ast::BinaryExpression(op, expr1, expr2);
    }
    | varUpdate {
        std::shared_ptr<comp::ast::varUpdate> var($1);
        $$ = new comp::ast::RExpression(var);
    }
    | LValue {
        std::shared_ptr<comp::ast::varIdentifier> var($1);
        $$ = new comp::ast::RExpression(var);
    }
    | OPEN_PAREN expr CLOSE_PAREN {
        std::shared_ptr<comp::ast::RExpression> expr($2);
        $$ = new comp::ast::RExpression(expr);
    }
    | SUBSTRACTION_OPERATOR expr {
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::UnaryMinus;
        std::shared_ptr<comp::ast::RExpression> expr($2);
        $$ = new comp::ast::UnaryExpression(op, expr);
    }
    | ADDITION_OPERATOR expr {
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::UnaryPlus;
        std::shared_ptr<comp::ast::RExpression> expr($2);
        $$ = new comp::ast::UnaryExpression(op, expr);
    }
    | NOT_OPERATOR expr {
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::LogicalNegation;
        std::shared_ptr<comp::ast::RExpression> expr($2);
        $$ = new comp::ast::UnaryExpression(op, expr);
    }
    | BINARY_ONES_COMPLEMENT_OPERATOR expr {
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::BitwiseComplement;
        std::shared_ptr<comp::ast::RExpression> expr($2);
        $$ = new comp::ast::UnaryExpression(op, expr);
    }
    | functionCall {
        std::shared_ptr<comp::ast::Identifier> functionCall($1);
        $$ = new comp::ast::RExpression(functionCall);
    }
    | identifier OPEN_PAREN CLOSE_PAREN {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        $$ = new comp::ast::RExpression(identifier);
    }
    | literalExpr {
        $$ = new comp::ast::Int64Literal($1, nullptr);
    }
    | expr ADDITION_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Addition, left, right, nullptr);
    }
    | expr SUBTRACTION_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Subtraction, left, right, nullptr);
    }
    | expr MULTIPLICATION_OPERATOR expr {
      std::shared_ptr<comp::ast::Expression> left($1);
      std::shared_ptr<comp::ast::Expression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Multiplication, left, right, nullptr);
    }
    | expr DIVISION_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Division, left, right, nullptr);
    }
    | expr REMAINDER_OPERATOR expr {
      std::shared_ptr<comp::ast::Expression> left($1);
      std::shared_ptr<comp::ast::Expression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Remainder, left, right, nullptr);
    }
    | expr EQUALITY_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Equality, left, right, nullptr);
    }
    | expr INEQUALITY_OPERATOR expr {
        std::shared_ptr<comp::ast::RExpression> left($1);
        std::shared_ptr<comp::ast::RExpression> right($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Inequality, left, right, nullptr);
    }
    | expr IDENTITY_OPERATOR expr {
        std::shared_ptr<comp::ast::RExpression> left($1);
        std::shared_ptr<comp::ast::RExpression> right($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Identity, left, right, nullptr);
    }
    | expr NONIDENTITY_OPERATOR expr {
        std::shared_ptr<comp::ast::RExpression> left($1);
        std::shared_ptr<comp::ast::RExpression> right($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Nonidentity, left, right, nullptr);
    }
    | expr COMMA_OPERATOR_OPERATOR expr {
        std::shared_ptr<comp::ast::RExpression> left($1);
        std::shared_ptr<comp::ast::RExpression> right($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::COMMA_OPERATOR, left, right, nullptr);
    }
    | expr GREATERTHAN_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Greaterthan, left, right, nullptr);
    }
    | expr GREATERTHANOREQUAL_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Greaterthanorequal, left, right, nullptr);
    }
    | expr LESSERTHAN_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Lesserthan, left, right, nullptr);
    }
    | expr LESSERTHANOREQUAL_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Lesserthanorequal, left, right, nullptr);
    }
    | expr LOGICALAND_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Logicaland, left, right, nullptr);
    }
    | expr LOGICALOR_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Logicalor, left, right, nullptr);
    }
    | expr XOR_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Xor, left, right, nullptr);
    }
    | expr ADDITIONASSIGNMENT_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Additionassignment, left, right, nullptr);
    }
    | expr SUBSTRACTIONASSIGNMENT_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Substractionassignment, left, right, nullptr);
    }
    | expr MULTIPLICATIONASSIGNMENT_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Multiplicationassignment, left, right, nullptr);
    }
    | expr DIVISIONASSIGNMENT_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Divisionassignment, left, right, nullptr);
    }
    | expr REMAINDREASSIGNMENT_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Remainderassignment, left, right, nullptr);
    }
    | expr EXPONENTIATIONASSIGNMENT_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Exponentiationassignment, left, right, nullptr);
    }
    | expr LEFTSHIFTASSIGNMENT_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Leftshiftassignment, left, right, nullptr);
    }
    | expr RIGHTSHIFTASSIGNMENT_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Rightshiftassignment, left, right, nullptr);
    }
    | expr BITWISEANDASSIGNMENT_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Bitwiseandassignment, left, right, nullptr);
    }
    | expr BITWISEXORASSIGNMENT_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Bitwisexorassignment, left, right, nullptr);
    }
    | expr BITWISEORASSIGNMENT_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      std::shared_ptr<comp::ast::RExpression> right($3);
      $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Bitwiseornassignment, left, right, nullptr);
    }
    | expr EXPONENTIATION_OPERATOR expr {
        std::shared_ptr<comp::ast::RExpression> left($1);
        std::shared_ptr<comp::ast::RExpression> right($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Exponentiation, left, right, nullptr);
    }
    | expr LEFTSHIFT_OPERATOR expr {
        std::shared_ptr<comp::ast::RExpression> left($1);
        std::shared_ptr<comp::ast::RExpression> right($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Leftshift, left, right, nullptr);
    }
    | expr RIGHTSHIFT_OPERATOR expr {
        std::shared_ptr<comp::ast::RExpression> left($1);
        std::shared_ptr<comp::ast::RExpression> right($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Rightshift, left, right, nullptr);
    }

    | expr LOGICALNOT_OPERATOR {
      std::shared_ptr<comp::ast::RExpression> left($1);
      $$ = new comp::ast::UnaryExpression(comp::ast::UnaryOperator::Greaterthan, left, nullptr);
    }
    | expr INCREMENT_OPERATOR {
      std::shared_ptr<comp::ast::RExpression> left($1);
      $$ = new comp::ast::UnaryExpression(comp::ast::UnaryOperator::Increment, left, nullptr);
    }
    | expr DECREMENT_OPERATOR {
      std::shared_ptr<comp::ast::RExpression> left($1);
      $$ = new comp::ast::UnaryExpression(comp::ast::UnaryOperator::Decrement, left, nullptr);
    }
    | UNARYNEGATION_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($2);
      $$ = new comp::ast::UnaryExpression(comp::ast::UnaryOperator::Unarynegation, left, nullptr);
    }
    | UNARYPLUS_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($2);
      $$ = new comp::ast::UnaryExpression(comp::ast::UnaryOperator::Unaryplus, left, nullptr);
    } */
%%
