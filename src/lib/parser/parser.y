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
  comp::ast::ConditionalExpression *conditionalExpression;
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
%token OR_OPERATOR AND_OPERATOR NOT_OPERATOR BINARY_ONES_COMPLEMENT_OPERATOR QUESTION_MARK COLON
%token SIMPLE_QUOTE
%token CHAR_TYPE INT32_TYPE INT64_TYPE VOID_TYPE

/* Typed tokens */
%token <uint8> CHAR_ATOM
%token <int64> INTEGER_LITERAL
%token <cstring> IDENTIFIER

/* AST nodes */ /*
%type <arrayDeclarator> */
%type <blockStatement> block /*
%type <callExpression> functionCall*/
%type <conditionalExpression> conditionalExpression
%type <dataType> arrayDataType dataType
%type <declarator> declarator
%type <function> functionDeclaration functionDefinition
%type <identifier> identifier /*
%type <lExpression> */
%type <identifierDataType> identifierDataType
%type <program> program root
%type <rExpression> charLiteral multiplicativeExpression additiveExpression primaryExpression shiftExpression relationalExpression equalityExpression andExpression exclusiveOrExpression inclusiveOrExpression logicalANDExpression logicalORExpression varUpdate
%type <unaryExpression> unaryExpression
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
%type <block_statement> blockContent block
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
  | declarationsList functionDefinition {
    std::shared_ptr<comp::ast::Function> functionDefinition($2);
    $1->push_back(functionDefinition);
    $$ = $1;
  }
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
  | identifier OPEN_BRACKET CLOSE_BRACKET {
    std::shared_ptr<comp::ast::Identifier> identifier($1);
    $$ = new comp::ast::ArrayDeclarator(comp::ast::IdentifierDeclarator::Create(identifier), nullptr);
  }
/*
  | identifier OPEN_BRACKET expression CLOSE_BRACKET {
    std::shared_ptr<comp::ast::Identifier> declarator($1);
    std::shared_ptr<comp::ast::Expression> size($3);
    $$ = new comp::ast::ArrayDeclarator(declarator, size);
  }
*/

functionDefinition:
    identifierDataType identifier OPEN_PAREN parametersList CLOSE_PAREN block {
        std::shared_ptr<comp::ast::DataType> return_type($1);
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        std::vector<std::shared_ptr<comp::ast::Parameter>> parametersList(*$4);
        delete($4);
        std::shared_ptr<comp::ast::BlockStatement> block($6);
        $$ = new comp::ast::Function(identifier, parametersList, return_type, block);
    }
    | identifierDataType identifier OPEN_PAREN CLOSE_PAREN block {
        std::shared_ptr<comp::ast::DataType> return_type($1);
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        std::shared_ptr<comp::ast::BlockStatement> block($5);
        $$ = new comp::ast::Function(identifier, {}, return_type, block);
    }

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
    | identifier OPEN_BRACE expression CLOSE_BRACKET {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        std::shared_ptr<comp::ast::Expression> expression($3);
        $$ = new comp::ast::LExpression(identifier, expression);
    }
    |  OPEN_PAREN LValue CLOSE_PAREN {
        std::shared_ptr<comp::ast::LValue> lval($3);
        $$ = new comp::ast::LExpression(lval);
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
    functionCallParams COMMA_OPERATOR expression {
        std::vector<std::shared_ptr<comp::ast::Parameter>> functionCallParams($1);
        std::shared_ptr<comp::ast::Expression> expression($3);
        $$ = new comp::ast::Parameter(functionCallParams, expression);
    }
    | expression {
        std::shared_ptr<comp::ast::Expression> expression($1);
        $$ = new comp::ast::Parameter(expression);
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
    expression SEMICOLON{
        std::shared_ptr<comp::ast::Expression> expression($1);
        $$ = new comp::ast::ExpressionStatement(expression);
    }

returnStatement:
    RETURN expressionOrVoid SEMICOLON {
        std::shared_ptr<comp::ast::Identifier> expression($2);
        $$ = new comp::ast::ReturnStatement(expression);
    }
    | RETURN SEMICOLON {
        $$ = new comp::ast::ReturnStatement();
    }

ifStatement:
    IF OPEN_PAREN expression CLOSE_PAREN statement ELSE statement {
        std::shared_ptr<comp::ast::RExpression> test($3);
        std::shared_ptr<comp::ast::Statement> consequence($5);
        std::shared_ptr<comp::ast::Statement> alternative($7);
        $$ = new comp::ast::IfStatement(comp::ast::IfStatement::test, consequence, alternative);
    }
    | IF OPEN_PAREN expression CLOSE_PAREN statement {
        std::shared_ptr<comp::ast::RExpression> expression($3);
        std::shared_ptr<comp::ast::Statement> consequence($5);
        $$ = new comp::ast::IfStatement(comp::ast::IfStatement::test, consequence);
    }

whileStatement:
    WHILE OPEN_PAREN expression CLOSE_PAREN statement {
        std::shared_ptr<comp::ast::RExpression> expression($3);
        std::shared_ptr<comp::ast::Statement> statement($5);
        $$ = new comp::ast::WhileStatement(expression, statement);
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
*/
block:
    /* OPEN_BRACE blockContent CLOSE_BRACE {
        std::shared_ptr<comp::ast::BlockStatement> blockContent($2);
        $$ = new comp::ast::BlockStatement(blockContent);
    }
    | */ OPEN_BRACE CLOSE_BRACE {
        $$ = new comp::ast::BlockStatement({});
    }
/*
blockContent:
    blockContent statement {
        std::shared_ptr<comp::ast::BlockStatement> blockContent($1);
        std::shared_ptr<comp::ast::Statement> statement($2);
        $$ = new comp::ast::BlockStatement(blockContent, instr);
    }
    | blockContent variableDeclaration {
        std::shared_ptr<comp::ast::BlockStatement> blockContent($1);
        std::shared_ptr<comp::ast::VariableDeclaration> variableDeclaration($2);
        $$ = new comp::ast::BlockStatement(blockContent, variableDeclaration);
    }

expressionOrVoid:
    expression{
        std::shared_ptr<comp::ast::RExpression> expression($1);
        $$ = new comp::ast::RExpression(expression);
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

expression:
    expression COMMA_OPERATOR expression {
        std::shared_ptr<comp::ast::RExpression> expr1($1);
        std::shared_ptr<comp::ast::RExpression> expr2($3);
        $$ = new comp::ast::RExpression(expr1, expr2);
    }
    | assignementExpression {
        std::shared_ptr<comp::ast::RExpression> assignementExpression($1);
        $$ = new comp::ast::RExpression(assignementExpression);
    }

assignementExpression:
    LValue SIMPLE_ASSIGNMENT_OPERATOR assignementExpression{
        std::shared_ptr<comp::ast::LValue> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignementExpression($3);
        $$ = new comp::ast::AssignementExpression(lValue, assignementExpression, comp::ast::AssignementOperator::Simple);

    }
    | LValue MULTP_ASSIGN_OPERATOR assignementExpression{
        std::shared_ptr<comp::ast::LValue> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignementExpression($3);
        $$ = new comp::ast::AssignementExpression(lValue, assignementExpression, comp::ast::AssignementOperator::Multiplication);

    }
    | LValue DIV_ASSIGN_OPERATOR assignementExpression{
        std::shared_ptr<comp::ast::LValue> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignementExpression($3);
        $$ = new comp::ast::AssignementExpression(lValue, assignementExpression, comp::ast::AssignementOperator::Division);

    }
    | LValue REM_ASSIGN_OPERATOR assignementExpression{
        std::shared_ptr<comp::ast::LValue> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignementExpression($3);
        $$ = new comp::ast::AssignementExpression(lValue, assignementExpression, comp::ast::AssignementOperator::Remainder);

    }
    | LValue ADD_ASSIGN_OPERATOR assignementExpression{
        std::shared_ptr<comp::ast::LValue> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignementExpression($3);
        $$ = new comp::ast::AssignementExpression(lValue, assignementExpression, comp::ast::AssignementOperator::Addition);

    }
    | LValue MINUS_ASSIGN_OPERATOR assignementExpression{
        std::shared_ptr<comp::ast::LValue> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignementExpression($3);
        $$ = new comp::ast::AssignementExpression(lValue, assignementExpression, comp::ast::AssignementOperator::Substraction);

    }
    | LValue LEFT_SHIFT_ASSIGN_OPERATOR assignementExpression{
        std::shared_ptr<comp::ast::LValue> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignementExpression($3);
        $$ = new comp::ast::AssignementExpression(lValue, assignementExpression, comp::ast::AssignementOperator::LeftShift);

    }
    | LValue RIGHT_SHIFT_ASSIGN_OPERATOR assignementExpression{
        std::shared_ptr<comp::ast::LValue> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignementExpression($3);
        $$ = new comp::ast::AssignementExpression(lValue, assignementExpression, comp::ast::AssignementOperator::RightShift);

    }
    | LValue AND_ASSIGN_OPERATOR assignementExpression{
        std::shared_ptr<comp::ast::LValue> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignementExpression($3);
        $$ = new comp::ast::AssignementExpression(lValue, assignementExpression, comp::ast::AssignementOperator::BitwiseAnd);

    }
    | LValue XOR_ASSIGN_OPERATOR assignementExpression{
        std::shared_ptr<comp::ast::LValue> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignementExpression($3);
        $$ = new comp::ast::AssignementExpression(lValue, assignementExpression, comp::ast::AssignementOperator::BitwiseXor);

    }
    | LValue OR_ASSIGN_OPERATOR assignementExpression{
        std::shared_ptr<comp::ast::LValue> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignementExpression($3);
        $$ = new comp::ast::AssignementExpression(lValue, assignementExpression, comp::ast::AssignementOperator::BitwiseOr);

    }
    | conditionalExpression {
        std::shared_ptr<comp::ast::ConditionalExpression> conditionalExpression($1);
        $$ = new comp::ast::AssignmentExpression(conditionalExpression);
    }

conditionalExpression:
    logicalOrExpression QUESTION_MARK expression COLON conditionalExpression{
        std::shared_ptr<comp::ast::BinaryExpression> logicalOrExpression($1);
        std::shared_ptr<comp::ast::RExpression> expression($3);
        std::shared_ptr<comp::ast::ConditionalExpression> conditionalExpression($5);
        $$ = new comp::ast::ConditionalExpression(logicalOrExpression, expression, conditionalExpression);
    }
    | logicalOrExpression {
        std::shared_ptr<comp::ast::BinaryExpression> logicalOrExpression($1);
        $$ = new comp::ast::ConditionalExpression(logicalOrExpression);
    }

logicalORExpression:
    logicalOrExpression OR_OPERATOR logicalAndExpression {
        std::shared_ptr<comp::ast::BinaryExpression> logicalOrExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> logicalAndExpression($3);
        $$ = new comp::ast::BinaryExpression(LogicalOr, logicalOrExpression, logicalAndExpression);
    }
    | logicalAndExpression {
        std::shared_ptr<comp::ast::BinaryExpression> logicalAndExpression($1);
        $$ = new comp::ast::BinaryExpression(logicalAndExpression);
    }

logicalANDExpression:
    logicalAndExpression AND_OPERATOR inclusiveOrExpression {
        std::shared_ptr<comp::ast::BinaryExpression> logicalAndExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> inclusiveOrExpression($3);
        $$ = new comp::ast::BinaryExpression(LogicalAnd, logicalAndExpression, inclusiveOrExpression);
    }
    | inclusiveOrExpression {
        std::shared_ptr<comp::ast::BinaryExpression> inclusiveOrExpression($1);
        $$ = new comp::ast::BinaryExpression(inclusiveOrExpression);
    }

inclusiveORExpression:
    inclusiveOrExpression BINARY_OR_OPERATOR exclusiveOrExpression {
        std::shared_ptr<comp::ast::BinaryExpression> inclusiveOrExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> exclusiveOrExpression($3);
        $$ = new comp::ast::BinaryExpression(BitwiseOr, inclusiveOrExpression, exclusiveOrExpression);
    }
    | exclusiveOrExpression {
        std::shared_ptr<comp::ast::BinaryExpression> exclusiveOrExpression($1);
        $$ = new comp::ast::BinaryExpression(exclusiveOrExpression);
    }

exclusiveORExpression:
    exclusiveOrExpression BINARY_XOR_OPERATOR andExpression {
        std::shared_ptr<comp::ast::BinaryExpression> exclusiveOrExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> andExpression($3);
        $$ = new comp::ast::BinaryExpression(BitwiseXor, exclusiveOrExpression, andExpression);
    }
    | andExpression {
        std::shared_ptr<comp::ast::BinaryExpression> andExpression($1);
        $$ = new comp::ast::BinaryExpression(andExpression);
    }

andExpression:
    andExpression BINARY_AND_OPERATOR equalityExpression {
        std::shared_ptr<comp::ast::BinaryExpression> andExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> equalityExpression($3);
        $$ = new comp::ast::BinaryExpression(BitwiseAnd, andExpression, equalityExpression);
    }
    | equalityExpression {
        std::shared_ptr<comp::ast::BinaryExpression> equalityExpression($1);
        $$ = new comp::ast::BinaryExpression(equalityExpression);
    }

equalityExpression:
    equalityExpression EQUALS_OPERATOR relationalExpression {
        std::shared_ptr<comp::ast::BinaryExpression> equalityExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> relationalExpression($3);
        $$ = new comp::ast::BinaryExpression(Equality, equalityExpression, relationalExpression);
    }
    | equalityExpression OR_ASSIGN_OPERATOR relationalExpression {
        std::shared_ptr<comp::ast::BinaryExpression> equalityExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> relationalExpression($3);
        $$ = new comp::ast::BinaryExpression(Inequality, equalityExpression, relationalExpression);
    }
    | relationalExpression {
        std::shared_ptr<comp::ast::BinaryExpression> relationalExpression($1);
        $$ = new comp::ast::BinaryExpression(relationalExpression);
    }

relationalExpression:
    relationalExpression GREATER_THAN_OPERATOR shiftExpression {
        std::shared_ptr<comp::ast::BinaryExpression> relationalExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> shiftExpression($3);
        $$ = new comp::ast::BinaryExpression(GreaterThan, equalityExpression, shiftExpression);
    }
    | relationalExpression LESS_THAN_OPERATOR shiftExpression {
        std::shared_ptr<comp::ast::BinaryExpression> relationalExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> shiftExpression($3);
        $$ = new comp::ast::BinaryExpression(LessThan, relationalExpression, shiftExpression);
    }
    | relationalExpression GREATER_THAN_OR_EQUAL_OPERATOR shiftExpression {
        std::shared_ptr<comp::ast::BinaryExpression> relationalExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> shiftExpression($3);
        $$ = new comp::ast::BinaryExpression(GreaterThanOrEqual, equalityExpression, shiftExpression);
    }
    | relationalExpression LESS_THAN_OR_EQUAL_OPERATOR shiftExpression {
        std::shared_ptr<comp::ast::BinaryExpression> relationalExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> shiftExpression($3);
        $$ = new comp::ast::BinaryExpression(LessThanOrEqualTo, relationalExpression, shiftExpression);
    }
    | shiftExpression {
        std::shared_ptr<comp::ast::BinaryExpression> shiftExpression($1);
        $$ = new comp::ast::BinaryExpression(shiftExpression);
    }

shiftExpression:
    shiftExpression RIGHT_SHIFT_OPERATOR additiveExpression {
        std::shared_ptr<comp::ast::BinaryExpression> shiftExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> additiveExpression($3);
        $$ = new comp::ast::BinaryExpression(RightShift, shiftExpression, additiveExpression);
    }
    | shiftExpression LEFT_SHIFT_OPERATOR additiveExpression {
        std::shared_ptr<comp::ast::BinaryExpression> shiftExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> additiveExpression($3);
        $$ = new comp::ast::BinaryExpression(LeftShift, shiftExpression, additiveExpression);
    }
    | additiveExpression {
        std::shared_ptr<comp::ast::BinaryExpression> additiveExpression($1);
        $$ = new comp::ast::BinaryExpression(additiveExpression);
    }

additiveExpression:
    additiveExpression ADDITION_OPERATOR multiplicativeExpression {
        std::shared_ptr<comp::ast::BinaryExpression> additiveExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> multiplicativeExpression($3);
        $$ = new comp::ast::BinaryExpression(Addition, additiveExpression, multiplicativeExpression);
    }
    | additiveExpression SUBTRACTION_OPERATOR multiplicativeExpression {
        std::shared_ptr<comp::ast::BinaryExpression> additiveExpression($1);
        std::shared_ptr<comp::ast::BinaryExpression> multiplicativeExpression($3);
        $$ = new comp::ast::BinaryExpression(Subtraction, additiveExpression, multiplicativeExpression);
    }
    | multiplicativeExpression {
        std::shared_ptr<comp::ast::BinaryExpression> multiplicativeExpression($1);
        $$ = new comp::ast::BinaryExpression(multiplicativeExpression);
    }

multiplicativeExpression:
    multiplicativeExpression MULTIPLICATION_OPERATOR unaryExpression {
        std::shared_ptr<comp::ast::BinaryExpression> multiplicativeExpression($1);
        std::shared_ptr<comp::ast::UnaryExpression> unaryExpression($3);
        $$ = new comp::ast::BinaryExpression(Multiplication, multiplicativeExpression, unaryExpression);
    }
    | multiplicativeExpression DIVISION_OPERATOR unaryExpression {
        std::shared_ptr<comp::ast::BinaryExpression> multiplicativeExpression($1);
        std::shared_ptr<comp::ast::UnaryExpression> unaryExpression($3);
        $$ = new comp::ast::BinaryExpression(Division, multiplicativeExpression, unaryExpression);
    }
    | multiplicativeExpression REMAINDER_OPERATOR unaryExpression {
        std::shared_ptr<comp::ast::BinaryExpression> multiplicativeExpression($1);
        std::shared_ptr<comp::ast::UnaryExpression> unaryExpression($3);
        $$ = new comp::ast::BinaryExpression(Remainder, multiplicativeExpression, unaryExpression);
    }
    | unaryExpression {
        std::shared_ptr<comp::ast::UnaryExpression> unaryExpression($1);
        $$ = new comp::ast::UnaryExpression(unaryExpression);
    }

unaryExpression:
    ADDITION_OPERATOR unaryExpression {
        std::shared_ptr<comp::ast::UnaryExpression> unaryExpression($1);
        $$ = new comp::ast::UnaryExpression(UnaryPlus, unaryExpression);
    }
    | SUBSTRACTION_OPERATOR unaryExpression {
        std::shared_ptr<comp::ast::UnaryExpression> unaryExpression($1);
        $$ = new comp::ast::UnaryExpression(UnaryMinus, unaryExpression);
    }
    | BINARY_ONES_COMPLEMENT_OPERATOR unaryExpression {
        std::shared_ptr<comp::ast::UnaryExpression> unaryExpression($1);
        $$ = new comp::ast::UnaryExpression(BitwiseComplement, unaryExpression);
    }
    | NOT_OPERATOR unaryExpression {
        std::shared_ptr<comp::ast::UnaryExpression> unaryExpression($1);
        $$ = new comp::ast::UnaryExpression(LogicalNegation, unaryExpression);
    }
    primaryExpression{
        std::shared_ptr<comp::ast::RExpression> primaryExpression($1);
        $$ = new comp::ast::RExpression(primaryExpression);
    }

primaryExpression:
    varUpdate{
        std::shared_ptr<comp::ast::RExpression> varUpdate($1);
        $$ = new comp::ast::RExpression(varUpdate);
    }
    | functionCall {
        std::shared_ptr<comp::ast::CallExpression> functionCall($1);
        $$ = new comp::ast::RExpression(functionCall);
    }
    | lValue {
        std::shared_ptr<comp::ast::LValue> lValue($1);
        $$ = new comp::ast::RExpression(lValue);
    }
    | OPEN_PAREN expression CLOSE_PAREN {
        std::shared_ptr<comp::ast::RExpression> expression($1);
        $$ = new comp::ast::RExpression(expression);
    }
    | literalExpr {
        std::shared_ptr<comp::ast::RExpression> literalExpr($1);
        $$ = new comp::ast::RExpression(literalExpr);
    }
*/
%%
