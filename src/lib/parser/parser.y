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
 uint8_t uint8;
 int64_t int64;
 char * s;
 comp::ast::RExpression *e;
 comp::ast::RExpression *expr;
 comp::ast::Program *program;
 comp::ast::Function *function;
 comp::ast::Identifier *identifier;
 comp::ast::DataType *dataType;
 comp::ast::UnaryOperator *unaryOperator;
 comp::ast::UnaryExpression *unaryExpression;
 comp::ast::ForStatement *for_statement;
 comp::ast::IfStatement *if_statement;
 comp::ast::WhileStatement *while_statement;
 comp::ast::BlockStatement *block;
 comp::ast::BlockStatement *insideBlock;
 comp::ast::ReturnStatement *return_statement;
 comp::ast::Statement *statement;
 comp::ast::LiteralDataType *dataTypeLiteral;
 comp::ast::ArrayDataType *arrayDataType;
 comp::ast::VariableDeclaration *variable_declaration;
 comp::ast::VariableDeclarator *variable_declarator;
 std::vector<std::shared_ptr<comp::ast::Declaration>> *declarationsList;
 std::vector<std::shared_ptr<comp::ast::VariableDeclarator>> *variableDeclaratorsList;
}

%token ADDITIONASSIGNMENT_OPERATOR BITWISEANDASSIGNMENT_OPERATOR BITWISEORASSIGNMENT_OPERATOR BITWISEXORASSIGNMENT_OPERATOR
%token DIVISIONASSIGNMENT_OPERATOR EQUALITY_OPERATOR EXPONENTIATIONASSIGNMENT_OPERATOR EXPONENTIATION_OPERATOR IDENTITY_OPERATOR
%token INEQUALITY_OPERATOR LEFTSHIFTASSIGNMENT_OPERATOR LEFTSHIFT_OPERATOR LITTERAL_EXPRESSION MULTIPLICATIONASSIGNMENT_OPERATOR
%token NONIDENTITY_OPERATOR REMAINDREASSIGNMENT_OPERATOR RIGHTSHIFTASSIGNMENT_OPERATOR RIGHTSHIFT_OPERATOR SUBSTRACTIONASSIGNMENT_OPERATOR
%token EQUAL_OPERATOR GREATERTHAN_OPERATOR GREATERTHANOREQUAL_OPERATOR LESSERTHAN_OPERATOR LESSERTHANOREQUAL_OPERATOR
%token EQUALEQUAL_OPERATOR LOGICALAND_OPERATOR LOGICALOR_OPERATOR LOGICALNOT_OPERATOR XOR_OPERATOR
%token SEMICOLON OPEN_BRACKET CLOSE_BRACKET INCREMENT_OPERATOR DECREMENT_OPERATOR OPEN_PAREN CLOSE_PAREN
%token IF ELSE WHILE FOR RETURN OPEN_BRACE CLOSE_BRACE
%token SIMPLE_ASSIGNMENT_OPERATOR COMMA_OPERATOR EQUALS_OPERATOR NOT_EQUAL_OPERATOR
%token LESS_THAN_OPERATOR LESS_THAN_OR_EQUAL_OPERATOR GREATER_THAN_OPERATOR GREATER_THAN_OR_EQUAL_OPERATOR
%token LEFT_SHIFT_OPERATOR RIGHT_SHIFT_OPERATOR
%token ADDITION_OPERATOR SUBTRACTION_OPERATOR DIVISION_OPERATOR MULTIPLICATION_OPERATOR REMAINDER_OPERATOR
%token ADD_ASSIGN_OPERATOR MINUS_ASSIGN_OPERATOR MULTP_ASSIGN_OPERATOR DIV_ASSIGN_OPERATOR REM_ASSIGN_OPERATOR
%token LEFT_SHIFT_ASSIGN_OPERATOR RIGHT_SHIFT_ASSIGN_OPERATOR AND_ASSIGN_OPERATOR XOR_ASSIGN_OPERATOR OR_ASSIGN_OPERATOR
%token BINARY_OR_OPERATOR BINARY_AND_OPERATOR BINARY_XOR_OPERATOR
%token OR_OPERATOR AND_OPERATOR NOT_OPERATOR BINARY_ONES_COMPLEMENT_OPERATOR
%token SIMPLE_QUOTE CONTROL_CHAR_ESCAPE HEX_CHAR_ESCAPE
%token INT32_TYPE INT64_TYPE CHAR IDENTIFIER


%token <i> INTEGER_LITERAL
%token <s> IDENTIFIER
%token <uint8> SOURCE_CHAR
%token <uint8> OCTAL_ESCAPE_SEQUENCE
%token <uint8> HEX_ESCAPE_SEQUENCE

%type <e> charLiteral expr intLiteral expressionOrVoid instr LiteralExpr literalExpr LITTERAL_EXPRESSION insideList nonEmptyDecParametersList
%type <uint8> charAtom
%type <program> program root
%type <function> function functionDeclaration functionDefinition
%type <identifier> identifier varIdentifier varIdentifierTabLiteral initial_value parametersList
%type <declarationsList> declarationsList
%type <variableDeclaratorsList> variableDeclaratorsList
%type <unaryExpression> unaryExpression varUpdate
%type <dataType> dataType
%type <variable_declarator> varDecAff suite suiteDecAff suiteDecAffLitteral varDec variable_declarator
%type <variable_declaration> varAff varDecAffLitteral paramsDefinition paramsDeclaration variableDeclaration
%type <statement> statement
%type <if_statement> if_statement
%type <dataTypeLiteral> dataTypeLiteral
%type <arrayDataType> arrayDataType
%type <while_statement> while_statement
%type <for_statement> for_statement
%type <block_statement> insideBlock block
%type <return_statement> return

%left SUBTRACTION_OPERATOR ADDITION_OPERATOR
%left MULTIPLICATION_OPERATOR DIVISION_OPERATOR
%left REMAINDER_OPERATOR

%%

root:
  program {
    root = $1;
  }

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
  | HEX_ESCAPE_SEQUENCE {
      $$ = $1;
  }

/* Généralités */
program:
    declarationsList {
        std::vector<std::shared_ptr<comp::ast::Declaration>> body(*$1);
        delete $1;
        $$ = new comp::ast::Program(body);
    }

declarationsList:
    /* declarationsList functionDeclaration{
        std::shared_ptr<comp::ast::Function> decl($2);
        $1->push_back(decl);
        $$ = $1;
    }
    | declarationsList functionDefinition {
        std::shared_ptr<comp::ast::Function> def($2);
        $1->push_back(def);
        $$ = $1;
    }
    | */ declarationsList variableDeclaration {
        std::shared_ptr<comp::ast::VariableDeclaration> variable_declaration($2);
        $1->push_back(variable_declaration);
        $$ = $1;
    }
    | {
        $$ = new std::vector<std::shared_ptr<comp::ast::Declaration>>();
    }

dataType:
    dataTypeLiteral {
        std::shared_ptr<comp::ast::LiteralDataType> type($1);
        $$ = new comp::ast::DataType(type);
    }
    | arrayDataType {
        std::shared_ptr<comp::ast::ArrayDataType> type($1);
        $$ = new comp::ast::DataType(type);
    }

dataTypeLiteral:
    identifier {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        $$ = new comp::ast::LiteralDataType(identifier);
    }

arrayDataType:
    dataTypeLiteral OPEN_BRACKET CLOSE_BRACKET{
        std::shared_ptr<comp::ast::LiteralDataType> type($1);
        $$ = new comp::ast::ArrayDataType(type);
    }

identifier:
    IDENTIFIER {
        $$ = new comp::ast::Identifier($1);
    }

/* Déclaration, affectation de variables */
variableDeclaration :
    dataTypeLiteral variableDeclaratorsList SEMICOLON{
        std::shared_ptr<comp::ast::LiteralDataType> dataType($1);
        std::vector<std::shared_ptr<comp::ast::VariableDeclarator>> declarators($2);
        $$ = new comp::ast::VariableDeclaration(dataType, declarators);
    }

variableDeclaratorsList:
    variableDeclaratorsList COMMA_OPERATOR variable_declarator{
        std::shared_ptr<comp::ast::VariableDeclarator> variable_declarator($3);
        $1->push_back(variable_declarator);
        $$ = $1;
    }
    /*
    | variable_declarator {
        $$ = new std::vector<std::shared_ptr<comp::ast::VariableDeclarator()>>;
        $$->push_back($1);
    }
    */
/*to remove*/
variable_declarator:
    SEMICOLON{
        $$ = new comp::ast::VariableDeclarator(nullptr, nullptr) ;
    }

/*varDecAffLitteral:
     varDecAffLitteral COMMA_OPERATOR suiteDecAffLitteral {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        std::shared_ptr<comp::ast::VariableDeclarator> declarators($3);
        $$ = new comp::ast::VariableDeclaration(identifier, declarators);
    }
    |  literalDataType suiteDecAffLitteral{
        std::shared_ptr<comp::ast::LiteralDataType> dataTypeLiteral($1);
        std::shared_ptr<comp::ast::VariableDeclarator> variable_declarator($2);
        std::vector<std::shared_ptr<comp::ast::VariableDeclarator>> variable_declarators;
        variable_declarators.push_back(variable_declarator);
        $$ = new comp::ast::VariableDeclaration(dataTypeLiteral, variable_declarators);
    }

suiteDecAffLitteral:
     varIdentifierTabLiteral {
    identifier {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        std::shared_ptr<comp::ast::IdentifierDeclarator> identifier_declarator = comp::ast::IdentifierDeclarator::Create(identifier);
        $$ = new comp::ast::VariableDeclarator(identifier_declarator, nullptr);
    }
     | identifier EQUAL_OPERATOR literalExpr{
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        std::shared_ptr<comp::ast::Expression> literalExpr($3);
        $$ = new comp::ast::VariableDeclarator(identifier, initial_value);
    }

varDecAff:
    varDecAff COMMA_OPERATOR suite {
        std::shared_ptr<comp::ast::VariableDeclaration> varDecAff($1);
        std::shared_ptr<comp::ast::VariableDeclarator> suite($3);
        $$ = new comp::ast::VariableDeclarator(varDecAff, suite);
    }
    | dataType suite {
        std::shared_ptr<comp::ast::DataType> dataType($1);
        std::shared_ptr<comp::ast::VariableDeclarator> suite($2);
        $$ = new comp::ast::VariableDeclarator(dataType, suite);
    }

suiteDecAff:
    varIdentifierTabLiteral {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        $$ = new comp::ast::VariableDeclarator(identifier);
    }
    | identifier EQUAL_OPERATOR expr {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        std::shared_ptr<comp::ast::Expression> expr($3);
        $$ = new comp::ast::VariableDeclarator(identifier, expr);
    }

varAff:
    varIdentifier EQUAL_OPERATOR expr{
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        std::shared_ptr<comp::ast::RExpression> expr($3);
        $$ = new comp::ast::VariableDeclarator(identifier, expr);
    }

varUpdate:
    varIdentifier INCREMENT_OPERATOR {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::PostfixIncrement;
        $$ = new comp::ast::UnaryExpression(op, identifier);
    }
    | varIdentifier DECREMENT_OPERATOR {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::PostfixDecrement;
        $$ = new comp::ast::UnaryExpression(op, identifier);
    }
    | INCREMENT_OPERATOR varIdentifier {
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::PrefixIncrement;
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        $$ = new comp::ast::UnaryExpression(op, identifier);
    }
    | DECREMENT_OPERATOR varIdentifier{
        comp::ast::UnaryOperator op = comp::ast::UnaryOperator::PrefixDecrement;
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        $$ = new comp::ast::UnaryExpression(op, identifier);
    }

varIdentifier:
    identifier {
        std::shared_ptr<std::vector<comp::ast::Identifier> identifier($1);
        $$ = new comp::ast::DataType(identifier);
    }
    | identifier OPEN_BRACKET expr CLOSE_BRACKET{
        std::shared_ptr<std::vector<comp::ast::Identifier> identifier($1);
        std::shared_ptr<std::vector<comp::ast::RExpression> expression($3);
        $$ = new comp::ast::DataType(identifier, expression);
    }

varIdentifierTabLiteral:
    identifier{
        std::shared_ptr<std::vector<comp::ast::Identifier> identifier($1);
        $$ = new comp::ast::DataType(identifier);
    }
    | identifier OPEN_BRACKET intLiteral CLOSE_BRACKET{
        std::shared_ptr<std::vector<comp::ast::Identifier> identifier($1);
        std::shared_ptr<std::vector<comp::ast::RExpression> expr($3);
        $$ = new comp::ast::DataType(identifier, expr);
    }
*/
/* instructions */
/*
instr:
    expr SEMICOLON {
        std::shared_ptr<comp::ast::RExpression> expr($1);
        $$ = new comp::ast::ExpressionStatement(epxr);
    }
    | block {
        $$ = new comp::ast::BlockStatement();
    }
    | if_statement {
        $$ = new comp::ast::IfStatement();
    }
    | while_statement {
        $$ = new comp::ast::WhileStatement();
    }
    | for_statement {
        $$ = new comp::ast::ForStatement();
    }
    | SEMICOLON{
    }

if_statement:
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

while_statement:
    WHILE OPEN_PAREN expr CLOSE_PAREN instr {
        std::shared_ptr<comp::ast::RExpression> expr($3);
        std::shared_ptr<comp::ast::Statement> body($5);
        $$ = new comp::ast::WhileStatement(expr, body);
    }

for_statement:
    FOR OPEN_PAREN expressionOrVoid SEMICOLON expressionOrVoid  SEMICOLON expressionOrVoid CLOSE_PAREN statement {
        std::shared_ptr<comp::ast::RExpression> initialization($3);
        std::shared_ptr<comp::ast::RExpression> condition($5);
        std::shared_ptr<comp::ast::RExpression> iteration($7);
        std::shared_ptr<comp::ast::RExpression> body($9);
        $$ = new comp::ast::ForStatement(initialization, condition, iteration, body);
    }
    | FOR OPEN_PAREN varDec expressionOrVoid SEMICOLON expressionOrVoid CLOSE_PAREN statement {
        std::shared_ptr<comp::ast::RExpression> initialization($3);
        std::shared_ptr<comp::ast::RExpression> condition($5);
        std::shared_ptr<comp::ast::RExpression> iteration($7);
        std::shared_ptr<comp::ast::RExpression> body($9);
        $$ = new comp::ast::ForStatement(initialization, condition, iteration, body);
    }


block:
    OPEN_BRACE insideBlock CLOSE_BRACE {
        std::shared_ptr<comp::ast::BlockStatement> insideBlock($2);
        $$ = new comp::ast::BlockStatement(insideBlock);
    }
    | OPEN_BRACE CLOSE_BRACE {
        $$ = new comp::ast::BlockStatement();
    }


insideBlock:
    insideBlock statement {
        std::shared_ptr<comp::ast::BlockStatement> insideBlock($1);
        std::shared_ptr<comp::ast::Statement> statement($2);
        $$ = new comp::ast::BlockStatement(insideBlock, instr);
    }
    | insideBlock varDec  {
        std::shared_ptr<comp::ast::BlockStatement> insideBlock($1);
        std::shared_ptr<comp::ast::VariableDeclarator> varDec($2);
        $$ = new comp::ast::BlockStatement(insideBlock, varDec);
    }

*/
/* Déclaration, définition de fonctions */
/*
paramsDec:
    paramsDef {
        std::shared_ptr<comp::ast::Identifier> paramsDef($1);
        $$ = new comp::ast::Parameter(paramsDef);
    }
    | dataType {
        std::shared_ptr<comp::ast::DataType> dataType($1);
        $$ = new comp::ast::Parameter(dataType);
    }
    | dataType OPEN_BRACKET CLOSE_BRACKET{
        std::shared_ptr<comp::ast::DataType> dataType($1);
        $$ = new comp::ast::Parameter(dataType);
    }

nonEmptyDecParametersList:
    nonEmptyDecParametersList COMMA_OPERATOR paramsDec {
        std::shared_ptr<comp::ast::RExpression> paramsList($1);
        std::shared_ptr<comp::ast::DataType> paramsDec($3);
        $$ = new comp::ast::Parameter(paramsList, paramsDec);
    }
    | paramsDec {
        std::shared_ptr<comp::ast::DataType> paramsDec($1);
        $$ = new comp::ast::Parameter(paramsDec);
    }

parametersList:
    parametersList COMMA_OPERATOR parameter {
        std::shared_ptr<comp::ast::Parameter> paramslist($1);
        std::shared_ptr<comp::ast::Parameter> parameter($3);
        $$ = new comp::ast::Parameter(paramslist, parameter);
    }
    | parameter {
        std::shared_ptr<comp::ast::Parameter> parameter($1);
        $$ = new comp::ast::Parameter(parameter);
    }

paramsDef:
    dataType identifier {
        std::shared_ptr<comp::ast::DataType> dataType($1);
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        $$ = new comp::ast::Parameter(dataType, identifier);
    }
    | dataType identifier OPEN_BRACKET CLOSE_BRACKET{
        std::shared_ptr<comp::ast::DataType> dataType($1);
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        $$ = new comp::ast::Parameter(dataType, identifier);
    }


nonEmptyDefParametersList:
    nonEmptyDefParametersList COMMA_OPERATOR paramsDef {

    }
    | paramsDef {

    }

parametersList:
    nonEmptyDefParametersList {

    }
    | {

    }

functionDeclaration:
    dataType identifier OPEN_PAREN parametersList CLOSE_PAREN SEMICOLON{
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        std::shared_ptr<comp::ast::Identifier> parametersList($4);
        $$ = new comp::ast::Function(identifier, parametersList);
    }

functionDefinition:
    dataType identifier OPEN_PAREN parametersList CLOSE_PAREN block{
        std::shared_ptr<comp::ast::Identifier> identifier($2);
        std::shared_ptr<comp::ast::Identifier> parametersList($4);
        std::shared_ptr<comp::ast::Block_Statement> block($6);
        $$ = new comp::ast::Function(identifier, parametersList, block);
    }

return:
    RETURN expressionOrVoid SEMICOLON{
        std::shared_ptr<comp::ast::Identifier> expr($2);
        $$ = new comp::ast::ReturnStatement(expr);
    }
*/
/* Expressions  */
/*
LiteralExpr:
    intLiteral {
        std::shared_ptr<comp::ast::Int64Literal> int($1);
        $$ = new comp::ast::RExpression(int);
    }
    | charLiteral {
        std::shared_ptr<comp::ast::Literal> char($1);
        $$ = new comp::ast::RExpression(char);
    }

expressionOrVoid:
    expr{
        std::shared_ptr<comp::ast::RExpression> expr($1);
        $$ = new comp::ast::RExpression(expr);
    }
    | {
        $$ = new comp::ast::RExpression();
    }

expression:
    INTEGER_LITERAL {
    $$ = new comp::ast::Int64Literal($1, nullptr);
    }
    | charLiteral {
    $$ = $1;
    }
    | expr op expr{
        std::shared_ptr<comp::ast::RExpression> expr1($1);
        std::shared_ptr<comp::ast::BinaryOperator> op($2);
        std::shared_ptr<comp::ast::RExpression> expr2($3);
        $$ = new comp::ast::BinaryExpression(op, expr1, expr2);
    }
    | varAff {
        std::shared_ptr<comp::ast::varAff> var($1);
        $$ = new comp::ast::RExpression(var);
    }
    | varUpdate {
        std::shared_ptr<comp::ast::varUpdate> var($1);
        $$ = new comp::ast::RExpression(var);
    }
    | varIdentifier {
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
    | identifier OPEN_PAREN insideList CLOSE_PAREN {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        std::shared_ptr<comp::ast::RExpression> expr($3);
        $$ = new comp::ast::RExpression(identifier, expr);
    }
    | identifier OPEN_PAREN CLOSE_PAREN {
        std::shared_ptr<comp::ast::Identifier> identifier($1);
        $$ = new comp::ast::RExpression(identifier);
    }
    | LITTERAL_EXPRESSION {
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
    }*/
    /*
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
      std::shared_ptr<comp::ast::RExpression> left($1);
      $$ = new comp::ast::UnaryExpression(comp::ast::UnaryOperator::Unarynegation, left, nullptr);
    }
    | UNARYPLUS_OPERATOR expr {
      std::shared_ptr<comp::ast::RExpression> left($1);
      $$ = new comp::ast::UnaryExpression(comp::ast::UnaryOperator::Unaryplus, left, nullptr);
    }*/

%%
