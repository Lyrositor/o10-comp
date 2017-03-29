%{

#include <iostream>
#include <comp/parser.h>
#include <comp/ast.h>
#include <memory>

#include <comp/parser/parser_config.h>

#define YYLLOC_DEFAULT(Cur, Rhs, N) \
  do \
    if (N) { \
      (Cur).first_index = YYRHSLOC(Rhs, 1).first_index; \
      (Cur).first_line = YYRHSLOC(Rhs, 1).first_line; \
      (Cur).first_column = YYRHSLOC(Rhs, 1).first_column; \
      (Cur).last_index = YYRHSLOC(Rhs, N).last_index; \
      (Cur).last_line = YYRHSLOC(Rhs, N).last_line; \
      (Cur).last_column = YYRHSLOC(Rhs, N).last_column; \
    } else { \
      (Cur).first_index = (Cur).last_index = YYRHSLOC(Rhs, 0).last_index; \
      (Cur).first_line = (Cur).last_line = YYRHSLOC(Rhs, 0).last_line; \
      (Cur).first_column = (Cur).last_column = YYRHSLOC(Rhs, 0).last_column; \
    } \
  while (0)

%}

%locations
%define api.pure full
%define parse.error verbose
%define parse.lac full

%lex-param {void *scanner}

%parse-param {void *scanner} {comp::ast::Program *&root}

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
  comp::ast::UnaryExpression *unaryExpression;
  comp::ast::Statement *statement;
  comp::ast::ForStatement *forStatement;
  comp::ast::IfStatement *ifStatement;
  comp::ast::WhileStatement *whileStatement;
  comp::ast::ForStatement *returnStatement;
  comp::ast::ExpressionStatement *expressionStatement;
  comp::ast::Parameter *parameter;
  comp::ast::VariableDeclaration *variableDeclaration;
  comp::ast::VariableDeclarator *variableDeclarator;
  /* Temporary vectors */
  std::vector<std::shared_ptr<comp::ast::Declaration>> *declarationsList;
  std::vector<std::shared_ptr<comp::ast::Parameter>> *parametersList;
  std::vector<std::shared_ptr<comp::ast::VariableDeclarator>> *variableDeclaratorsList;
  std::vector<std::shared_ptr<comp::ast::Statement>> *statementsList;
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
%type <blockStatement> block
%type <callExpression> functionCall
%type <dataType> arrayDataType dataType
%type <declarator> declarator
%type <function> functionDeclaration functionDefinition
%type <identifier> identifier
%type <lExpression> lExpression LValue
%type <identifierDataType> identifierDataType
%type <program> program root
%type <rExpression> assignmentExpression charLiteral expression hexIntegerLiteral unaryExpression multiplicativeExpression conditionalExpression additiveExpression primaryExpression shiftExpression relationalExpression equalityExpression ANDExpression exclusiveORExpression inclusiveORExpression logicalANDExpression logicalORExpression  varUpdate literalExpr
%type <statement> forStatement ifStatement returnStatement statement whileStatement
%type <expressionStatement> expressionStatement
%type <parameter> parameter
%type <variableDeclaration> variableDeclaration
%type <variableDeclarator> variableDeclarator

/* Temporary vectors */
%type <declarationsList> declarationsList
%type <parametersList> parametersList functionCallParams
%type <variableDeclaratorsList> variableDeclaratorsList
%type <statementsList> blockContent

%left SUBTRACTION_OPERATOR ADDITION_OPERATOR
%left MULTIPLICATION_OPERATOR DIVISION_OPERATOR
%left REMAINDER_OPERATOR


%%
root:
  program {
    root = $1;
  }

program:
  declarationsList {
    std::vector<std::shared_ptr<comp::ast::Declaration>> body(*$1);
    delete $1;
    $$ = new comp::ast::Program(body, LOCATION(&@1));
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
    $$ = new comp::ast::Function(identifier, parameters, return_type, nullptr, LOCATION(&@1));
  }
  | identifierDataType identifier OPEN_PAREN CLOSE_PAREN SEMICOLON {
    std::shared_ptr<comp::ast::DataType> return_type($1);
    std::shared_ptr<comp::ast::Identifier> identifier($2);
    $$ = new comp::ast::Function(identifier, {}, return_type, nullptr, LOCATION(&@1));
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
    $$ = new comp::ast::IdentifierDataType(comp::ast::Identifier::Create("char", LOCATION(&@1)), LOCATION(&@1));
  }
  | INT32_TYPE {
    $$ = new comp::ast::IdentifierDataType(comp::ast::Identifier::Create("int32_t", LOCATION(&@1)), LOCATION(&@1));
  }
  | INT64_TYPE {
    $$ = new comp::ast::IdentifierDataType(comp::ast::Identifier::Create("int64_t", LOCATION(&@1)), LOCATION(&@1));
  }
  | VOID_TYPE {
    $$ = new comp::ast::IdentifierDataType(comp::ast::Identifier::Create("void", LOCATION(&@1)), LOCATION(&@1));
  }

arrayDataType:
  identifierDataType OPEN_BRACKET CLOSE_BRACKET{
    std::shared_ptr<comp::ast::DataType> item_type($1);
    $$ = new comp::ast::ArrayDataType(item_type, nullptr, LOCATION(&@1));
  }

identifier:
  IDENTIFIER {
    $$ = new comp::ast::Identifier($1, LOCATION(&@1));
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
    $$ = new comp::ast::NamedParameter(literal_data_type, declarator, LOCATION(&@1));
  }
  | dataType {
    std::shared_ptr<comp::ast::DataType> dataType($1);
    $$ = new comp::ast::AnonymousParameter(dataType, LOCATION(&@1));
  }

declarator:
  identifier {
    std::shared_ptr<comp::ast::Identifier> identifier($1);
    $$ = new comp::ast::IdentifierDeclarator(identifier, LOCATION(&@1));
  }
  | identifier OPEN_BRACKET CLOSE_BRACKET {
    std::shared_ptr<comp::ast::Identifier> identifier($1);
    $$ = new comp::ast::ArrayDeclarator(comp::ast::IdentifierDeclarator::Create(identifier, identifier->location), nullptr, LOCATION(&@1));
  }
/*
  | identifier OPEN_BRACKET expression CLOSE_BRACKET {
    std::shared_ptr<comp::ast::Identifier> identifier($1);
    std::shared_ptr<comp::ast::Expression> size($3);
    $$ = new comp::ast::ArrayDeclarator(identifier, size, LOCATION(&@1));
  }
*/

functionDefinition:
    identifierDataType identifier OPEN_PAREN parametersList CLOSE_PAREN block {
        std::shared_ptr<comp::ast::DataType> return_type($1);
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        std::vector<std::shared_ptr<comp::ast::Parameter>> parametersList(*$4);
        delete($4);
        std::shared_ptr<comp::ast::BlockStatement> block($6);
        $$ = new comp::ast::Function(identifier, parametersList, return_type, block, LOCATION(&@1));
    }
    | identifierDataType identifier OPEN_PAREN CLOSE_PAREN block {
        std::shared_ptr<comp::ast::DataType> return_type($1);
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        std::shared_ptr<comp::ast::BlockStatement> block($5);
        $$ = new comp::ast::Function(identifier, {}, return_type, block, LOCATION(&@1));
    }

variableDeclaration:
  identifierDataType variableDeclaratorsList SEMICOLON {
    std::shared_ptr<comp::ast::IdentifierDataType> base_type($1);
    std::vector<std::shared_ptr<comp::ast::VariableDeclarator>> declarators(*$2);
    delete $2;
    $$ = new comp::ast::VariableDeclaration(base_type, declarators, LOCATION(&@1));
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
      $$ = new comp::ast::VariableDeclarator(declarator, nullptr, LOCATION(&@1));
  }
  | declarator SIMPLE_ASSIGNMENT_OPERATOR expression {
      std::shared_ptr<comp::ast::Declarator> decl($1);
      std::shared_ptr<comp::ast::RExpression> expression($3);
      $$ = new comp::ast::VariableDeclarator(decl, expression, LOCATION(&@1));
  }


LValue:
    identifier {
        $$ = $1;
    }
    | identifier OPEN_BRACKET expression CLOSE_BRACKET {
        std::shared_ptr<comp::ast::RExpression> array($1);
        std::shared_ptr<comp::ast::RExpression> index($3);
        $$ = new comp::ast::SubscriptExpression(array, index, LOCATION(&@1));
    }
    |  OPEN_PAREN LValue CLOSE_PAREN {
        $$ = $2;
    }

varUpdate:
    LValue INCREMENT_OPERATOR {
        std::shared_ptr<comp::ast::LExpression> LValue($1);
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::PostfixIncrement;
        $$ = new comp::ast::UnaryExpression(op, LValue, LOCATION(&@1));
    }
    | LValue DECREMENT_OPERATOR {
        std::shared_ptr<comp::ast::LExpression> LValue($1);
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::PostfixDecrement;
        $$ = new comp::ast::UnaryExpression(op, LValue, LOCATION(&@1));
    }
    | INCREMENT_OPERATOR LValue {
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::PrefixIncrement;
        std::shared_ptr<comp::ast::LExpression> LValue($2);
        $$ = new comp::ast::UnaryExpression(op, LValue, LOCATION(&@1));
    }
    | DECREMENT_OPERATOR LValue{
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::PrefixDecrement;
        std::shared_ptr<comp::ast::LExpression> LValue($2);
        $$ = new comp::ast::UnaryExpression(op, LValue, LOCATION(&@1));
    }

functionCall:
    identifier OPEN_PAREN functionCallParams CLOSE_PAREN {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        std::vector<std::shared_ptr<comp::ast::Parameter>> arguments(*$3);
        delete $3;
        $$ = new comp::ast::CallExpression(identifier, arguments, LOCATION(&@1));
    }
    | identifier OPEN_PAREN CLOSE_PAREN {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        $$ = new comp::ast::CallExpression(identifier, {}, LOCATION(&@1));
    }

functionCallParams:
    functionCallParams COMMA_OPERATOR expression {
        std::shared_ptr<comp::ast::RExpression> expression($3);
        $1->push_back(expression, LOCATION(&@1));
        $$ = $1;
    }
    | expression {
        std::shared_ptr<comp::ast::RExpression> expression($1);
        $$ = new std::vector<std::shared_ptr<comp::ast::Parameter>>;
        $$->push_back(expression, LOCATION(&@1));
    }

statement:
    expressionStatement {
        $$ = $1;
    }
    | returnStatement {
        $$ = $1;
    }
    | block {
        $$ = $1;
    }
    | /* ifStatement {
        $$ = $1;
    }
    | whileStatement {
        $$ = $1;
    }
    | forStatement {
        $$ = $1;
    }
    |*/ SEMICOLON{
        $$ = new comp::ast::NullStatement(LOCATION(&@1));
    }

expressionStatement:
    expression SEMICOLON {
        std::shared_ptr<comp::ast::RExpression> expression($1);
        $$ = new comp::ast::ExpressionStatement(expression, LOCATION(&@1));
    }

returnStatement:
    RETURN expression SEMICOLON {
        std::shared_ptr<comp::ast::RExpression> expression($2);
        $$ = new comp::ast::ReturnStatement(expression, LOCATION(&@1));
    }
    | RETURN SEMICOLON {
        $$ = new comp::ast::ReturnStatement(nullptr, LOCATION(&@1));
    }

/*

ifStatement:
    IF OPEN_PAREN expression CLOSE_PAREN statement ELSE statement {
        std::shared_ptr<comp::ast::RExpression> test($3);
        std::shared_ptr<comp::ast::Statement> consequence($5);
        std::shared_ptr<comp::ast::Statement> alternative($7);
        $$ = new comp::ast::IfStatement(comp::ast::IfStatement::test, consequence, alternative, LOCATION(&@1));
    }
    | IF OPEN_PAREN expression CLOSE_PAREN statement {
        std::shared_ptr<comp::ast::RExpression> expression($3);
        std::shared_ptr<comp::ast::Statement> consequence($5);
        $$ = new comp::ast::IfStatement(comp::ast::IfStatement::test, consequence, LOCATION(&@1));
    }

whileStatement:
    WHILE OPEN_PAREN expression CLOSE_PAREN statement {
        std::shared_ptr<comp::ast::RExpression> expression($3);
        std::shared_ptr<comp::ast::Statement> statement($5);
        $$ = new comp::ast::WhileStatement(expression, statement, LOCATION(&@1));
    }

forStatement:
    FOR OPEN_PAREN expressionOrVoid SEMICOLON expressionOrVoid SEMICOLON expressionOrVoid CLOSE_PAREN statement {
        std::shared_ptr<comp::ast::RExpression> initialization($3);
        std::shared_ptr<comp::ast::RExpression> condition($5);
        std::shared_ptr<comp::ast::RExpression> iteration($7);
        std::shared_ptr<comp::ast::Statement> body($9);
        $$ = new comp::ast::ForStatement(initialization, condition, iteration, body, LOCATION(&@1));
    }
    | FOR OPEN_PAREN variableDeclaration expressionOrVoid SEMICOLON expressionOrVoid CLOSE_PAREN statement {
        std::shared_ptr<comp::ast::VariableDeclaration> initialization($3);
        std::shared_ptr<comp::ast::RExpression> condition($4);
        std::shared_ptr<comp::ast::RExpression> iteration($6);
        std::shared_ptr<comp::ast::Statement> body($8);
        $$ = new comp::ast::ForStatement(initialization, condition, iteration, body, LOCATION(&@1));
    }

*/

block:
     OPEN_BRACE blockContent CLOSE_BRACE {
        std::vector<std::shared_ptr<comp::ast::Statement>> body(*$2);
        delete $2;
        $$ = new comp::ast::BlockStatement(body, LOCATION(&@1));
    }
    | OPEN_BRACE CLOSE_BRACE {
        $$ = new comp::ast::BlockStatement({}, LOCATION(&@1));
    }

blockContent:
    blockContent statement {
        std::shared_ptr<comp::ast::Statement> statement($2);
        $1->push_back(statement);
        $$ = $1;
    }
    | blockContent variableDeclaration {
        std::shared_ptr<comp::ast::Statement> statement($2);
        $1->push_back(statement);
        $$ = $1;
    }
    | variableDeclaration {
        std::shared_ptr<comp::ast::Statement> statement($1);
        $$ = new std::vector<std::shared_ptr<comp::ast::Statement>>();
        $$->push_back(statement);
    }
    | statement {
        std::shared_ptr<comp::ast::Statement> statement($1);
        $$ = new std::vector<std::shared_ptr<comp::ast::Statement>>();
        $$->push_back(statement);
    }

literalExpr:
    INTEGER_LITERAL {
        $$ = new comp::ast::Int64Literal($1, LOCATION(&@1));
    }
    | charLiteral {
        $$ = $1;
    }

charLiteral:
    SIMPLE_QUOTE CHAR_ATOM SIMPLE_QUOTE {
        $$ = new comp::ast::Uint8Literal($2, LOCATION(&@1));
    }

expression:
    expression COMMA_OPERATOR expression {
        std::shared_ptr<comp::ast::RExpression> expr1($1);
        std::shared_ptr<comp::ast::RExpression> expr2($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Comma, expr1, expr2, LOCATION(&@1));
    }
    | assignmentExpression {
        $$ = $1;
    }

assignmentExpression:
    LValue SIMPLE_ASSIGNMENT_OPERATOR assignmentExpression {
        std::shared_ptr<comp::ast::LExpression> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignmentExpression($3);
        $$ = new comp::ast::AssignmentExpression(lValue, assignmentExpression, comp::ast::AssignmentOperator::Simple, LOCATION(&@1));

    }
    | LValue MULTP_ASSIGN_OPERATOR assignmentExpression {
        std::shared_ptr<comp::ast::LExpression> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignmentExpression($3);
        $$ = new comp::ast::AssignmentExpression(lValue, assignmentExpression, comp::ast::AssignmentOperator::Multiplication, LOCATION(&@1));

    }
    | LValue DIV_ASSIGN_OPERATOR assignmentExpression{
        std::shared_ptr<comp::ast::LExpression> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignmentExpression($3);
        $$ = new comp::ast::AssignmentExpression(lValue, assignmentExpression, comp::ast::AssignmentOperator::Division, LOCATION(&@1));

    }
    | LValue REM_ASSIGN_OPERATOR assignmentExpression{
        std::shared_ptr<comp::ast::LExpression> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignmentExpression($3);
        $$ = new comp::ast::AssignmentExpression(lValue, assignmentExpression, comp::ast::AssignmentOperator::Remainder, LOCATION(&@1));

    }
    | LValue ADD_ASSIGN_OPERATOR assignmentExpression{
        std::shared_ptr<comp::ast::LExpression> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignmentExpression($3);
        $$ = new comp::ast::AssignmentExpression(lValue, assignmentExpression, comp::ast::AssignmentOperator::Addition, LOCATION(&@1));

    }
    | LValue MINUS_ASSIGN_OPERATOR assignmentExpression{
        std::shared_ptr<comp::ast::LExpression> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignmentExpression($3);
        $$ = new comp::ast::AssignmentExpression(lValue, assignmentExpression, comp::ast::AssignmentOperator::Subtraction, LOCATION(&@1));

    }
    | LValue LEFT_SHIFT_ASSIGN_OPERATOR assignmentExpression{
        std::shared_ptr<comp::ast::LExpression> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignmentExpression($3);
        $$ = new comp::ast::AssignmentExpression(lValue, assignmentExpression, comp::ast::AssignmentOperator::LeftShift, LOCATION(&@1));

    }
    | LValue RIGHT_SHIFT_ASSIGN_OPERATOR assignmentExpression{
        std::shared_ptr<comp::ast::LExpression> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignmentExpression($3);
        $$ = new comp::ast::AssignmentExpression(lValue, assignmentExpression, comp::ast::AssignmentOperator::RightShift, LOCATION(&@1));

    }
    | LValue AND_ASSIGN_OPERATOR assignmentExpression{
        std::shared_ptr<comp::ast::LExpression> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignmentExpression($3);
        $$ = new comp::ast::AssignmentExpression(lValue, assignmentExpression, comp::ast::AssignmentOperator::BitwiseAnd, LOCATION(&@1));

    }
    | LValue XOR_ASSIGN_OPERATOR assignmentExpression{
        std::shared_ptr<comp::ast::LExpression> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignmentExpression($3);
        $$ = new comp::ast::AssignmentExpression(lValue, assignmentExpression, comp::ast::AssignmentOperator::BitwiseXor, LOCATION(&@1));

    }
    | LValue OR_ASSIGN_OPERATOR assignmentExpression{
        std::shared_ptr<comp::ast::LExpression> lValue($1);
        std::shared_ptr<comp::ast::RExpression> assignmentExpression($3);
        $$ = new comp::ast::AssignmentExpression(lValue, assignmentExpression, comp::ast::AssignmentOperator::BitwiseOr, LOCATION(&@1));

    }
    | conditionalExpression {
        $$ = $1;
    }

conditionalExpression:
    logicalORExpression QUESTION_MARK expression COLON conditionalExpression{
        std::shared_ptr<comp::ast::RExpression> logicalOrExpression($1);
        std::shared_ptr<comp::ast::RExpression> expression($3);
        std::shared_ptr<comp::ast::RExpression> conditionalExpression($5);
        $$ = new comp::ast::ConditionalExpression(logicalOrExpression, expression, conditionalExpression, LOCATION(&@1));
    }
    | logicalORExpression {
        $$ = $1;
    }

logicalORExpression:
    logicalORExpression OR_OPERATOR logicalANDExpression {
        std::shared_ptr<comp::ast::RExpression> logicalOrExpression($1);
        std::shared_ptr<comp::ast::RExpression> logicalAndExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::LogicalOr, logicalOrExpression, logicalAndExpression, LOCATION(&@1));
    }
    | logicalANDExpression {
        $$ = $1;
    }

logicalANDExpression:
    logicalANDExpression AND_OPERATOR inclusiveORExpression {
        std::shared_ptr<comp::ast::RExpression> logicalAndExpression($1);
        std::shared_ptr<comp::ast::RExpression> inclusiveOrExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::LogicalAnd, logicalAndExpression, inclusiveOrExpression, LOCATION(&@1));
    }
    | inclusiveORExpression {
        $$ = $1;
    }

inclusiveORExpression:
    inclusiveORExpression BINARY_OR_OPERATOR exclusiveORExpression {
        std::shared_ptr<comp::ast::RExpression> inclusiveOrExpression($1);
        std::shared_ptr<comp::ast::RExpression> exclusiveOrExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::BitwiseOr, inclusiveOrExpression, exclusiveOrExpression, LOCATION(&@1));
    }
    | exclusiveORExpression {
        $$ = $1;
    }

exclusiveORExpression:
    exclusiveORExpression BINARY_XOR_OPERATOR ANDExpression {
        std::shared_ptr<comp::ast::RExpression> exclusiveOrExpression($1);
        std::shared_ptr<comp::ast::RExpression> andExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::BitwiseXor, exclusiveOrExpression, andExpression, LOCATION(&@1));
    }
    | ANDExpression {
        $$ = $1;
    }

ANDExpression:
    ANDExpression BINARY_AND_OPERATOR equalityExpression {
        std::shared_ptr<comp::ast::RExpression> andExpression($1);
        std::shared_ptr<comp::ast::RExpression> equalityExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::BitwiseAnd, andExpression, equalityExpression, LOCATION(&@1));
    }
    | equalityExpression {
        $$ = $1;
    }

equalityExpression:
    equalityExpression EQUALS_OPERATOR relationalExpression {
        std::shared_ptr<comp::ast::RExpression> equalityExpression($1);
        std::shared_ptr<comp::ast::RExpression> relationalExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Equality, equalityExpression, relationalExpression, LOCATION(&@1));
    }
    | equalityExpression OR_ASSIGN_OPERATOR relationalExpression {
        std::shared_ptr<comp::ast::RExpression> equalityExpression($1);
        std::shared_ptr<comp::ast::RExpression> relationalExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Inequality, equalityExpression, relationalExpression, LOCATION(&@1));
    }
    | relationalExpression {
        $$ = $1;
    }

relationalExpression:
    relationalExpression GREATER_THAN_OPERATOR shiftExpression {
        std::shared_ptr<comp::ast::RExpression> relationalExpression($1);
        std::shared_ptr<comp::ast::RExpression> shiftExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::GreaterThan, relationalExpression, shiftExpression, LOCATION(&@1));
    }
    | relationalExpression LESS_THAN_OPERATOR shiftExpression {
        std::shared_ptr<comp::ast::RExpression> relationalExpression($1);
        std::shared_ptr<comp::ast::RExpression> shiftExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::LessThan, relationalExpression, shiftExpression, LOCATION(&@1));
    }
    | relationalExpression GREATER_THAN_OR_EQUAL_OPERATOR shiftExpression {
        std::shared_ptr<comp::ast::RExpression> relationalExpression($1);
        std::shared_ptr<comp::ast::RExpression> shiftExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::GreaterThanOrEqual, relationalExpression, shiftExpression, LOCATION(&@1));
    }
    | relationalExpression LESS_THAN_OR_EQUAL_OPERATOR shiftExpression {
        std::shared_ptr<comp::ast::RExpression> relationalExpression($1);
        std::shared_ptr<comp::ast::RExpression> shiftExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::LessThanOrEqualTo, relationalExpression, shiftExpression, LOCATION(&@1));
    }
    | shiftExpression {
        $$ = $1;
    }

shiftExpression:
    shiftExpression RIGHT_SHIFT_OPERATOR additiveExpression {
        std::shared_ptr<comp::ast::RExpression> shiftExpression($1);
        std::shared_ptr<comp::ast::RExpression> additiveExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::RightShift, shiftExpression, additiveExpression, LOCATION(&@1));
    }
    | shiftExpression LEFT_SHIFT_OPERATOR additiveExpression {
        std::shared_ptr<comp::ast::RExpression> shiftExpression($1);
        std::shared_ptr<comp::ast::RExpression> additiveExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::LeftShift, shiftExpression, additiveExpression, LOCATION(&@1));
    }
    | additiveExpression {
        $$ = $1;
    }

additiveExpression:
    additiveExpression ADDITION_OPERATOR multiplicativeExpression {
        std::shared_ptr<comp::ast::RExpression> additiveExpression($1);
        std::shared_ptr<comp::ast::RExpression> multiplicativeExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Addition, additiveExpression, multiplicativeExpression, LOCATION(&@1));
    }
    | additiveExpression SUBTRACTION_OPERATOR multiplicativeExpression {
        std::shared_ptr<comp::ast::RExpression> additiveExpression($1);
        std::shared_ptr<comp::ast::RExpression> multiplicativeExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Subtraction, additiveExpression, multiplicativeExpression, LOCATION(&@1));
    }
    | multiplicativeExpression {
        $$ = $1;
    }

multiplicativeExpression:
    multiplicativeExpression MULTIPLICATION_OPERATOR unaryExpression {
        std::shared_ptr<comp::ast::RExpression> multiplicativeExpression($1);
        std::shared_ptr<comp::ast::RExpression> unaryExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Multiplication, multiplicativeExpression, unaryExpression, LOCATION(&@1));
    }
    | multiplicativeExpression DIVISION_OPERATOR unaryExpression {
        std::shared_ptr<comp::ast::RExpression> multiplicativeExpression($1);
        std::shared_ptr<comp::ast::RExpression> unaryExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Division, multiplicativeExpression, unaryExpression, LOCATION(&@1));
    }
    | multiplicativeExpression REMAINDER_OPERATOR unaryExpression {
        std::shared_ptr<comp::ast::RExpression> multiplicativeExpression($1);
        std::shared_ptr<comp::ast::RExpression> unaryExpression($3);
        $$ = new comp::ast::BinaryExpression(comp::ast::BinaryOperator::Remainder, multiplicativeExpression, unaryExpression, LOCATION(&@1));
    }
    | unaryExpression {
        $$ = $1;
    }

unaryExpression:
    ADDITION_OPERATOR unaryExpression {
        std::shared_ptr<comp::ast::RExpression> unaryExpression($2);
        $$ = new comp::ast::UnaryExpression(comp::ast::UnaryOperator::UnaryPlus, unaryExpression, LOCATION(&@1));
    }
    | SUBSTRACTION_OPERATOR unaryExpression {
        std::shared_ptr<comp::ast::RExpression> unaryExpression($2);
        $$ = new comp::ast::UnaryExpression(comp::ast::UnaryOperator::UnaryMinus, unaryExpression, LOCATION(&@1));
    }
    | BINARY_ONES_COMPLEMENT_OPERATOR unaryExpression {
        std::shared_ptr<comp::ast::RExpression> unaryExpression($2);
        $$ = new comp::ast::UnaryExpression(comp::ast::UnaryOperator::BitwiseComplement, unaryExpression, LOCATION(&@1));
    }
    | NOT_OPERATOR unaryExpression {
        std::shared_ptr<comp::ast::RExpression> unaryExpression($2);
        $$ = new comp::ast::UnaryExpression(comp::ast::UnaryOperator::LogicalNegation, unaryExpression, LOCATION(&@1));
    }
    | primaryExpression{
        $$ = $1;
    }

primaryExpression:
    varUpdate{
        $$ = $1;
    }
    | functionCall {
        $$ = $1;
    }
    | LValue {
        $$ = $1;
    }
    | OPEN_PAREN expression CLOSE_PAREN {
        $$ = $2;
    }
    | literalExpr {
        $$ = $1;
    }
%%
