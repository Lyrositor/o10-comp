#include <comp/ast/for_statement.h>
#include <comp/ast.h>

namespace comp {
namespace ast {

// FOR STATEMENT
std::unique_ptr<ForStatement> ForStatement::Create(
  std::shared_ptr<ForStatementInitializer> initialization,
  std::shared_ptr<RExpression> condition,
  std::shared_ptr<RExpression> iteration,
  std::shared_ptr<Statement> body,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<ForStatement>(
    new ForStatement(initialization, condition, iteration, body, location));
}

ForStatement::ForStatement(
  std::shared_ptr<ForStatementInitializer> initialization,
  std::shared_ptr<RExpression> condition,
  std::shared_ptr<RExpression> iteration,
  std::shared_ptr<Statement> body,
  std::shared_ptr<SourceLocation> location
) :
  Statement(Type::ForStatement, location),
  initialization(initialization),
  condition(condition),
  iteration(iteration),
  body(body) {
}

// FOR_STATEMENT_INITIALIZER
ForStatementInitializer::ForStatementInitializer(
    Type initializerType,
    std::shared_ptr<SourceLocation> location
) :
    Node(initializerType,location) {
}
ForStatementInitializer::~ForStatementInitializer() {
}

// FOR_STAT_EXPR_INITIALIZER
ForStatExprInitializer::ForStatExprInitializer(
    std::shared_ptr<RExpression> exprInit,
    std::shared_ptr<SourceLocation> location
) :
    ForStatementInitializer(Type::ForStatExprInit, location),
    exprInit(exprInit) {
}

std::unique_ptr<ForStatExprInitializer> ForStatExprInitializer::Create(
    std::shared_ptr<RExpression> exprInit,
    std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<ForStatExprInitializer>(
      new ForStatExprInitializer(exprInit, location));
}

ForStatExprInitializer::~ForStatExprInitializer() {
}


// FOR_STAT_DECL_INITIALIZER
ForStatDeclInitializer::ForStatDeclInitializer(
    std::shared_ptr<VariableDeclaration> variableDeclaration,
    std::shared_ptr<SourceLocation> location
) :
    ForStatementInitializer(Type::ForStatDeclInit, location),
    variableDeclaration(variableDeclaration) {
}

std::unique_ptr<ForStatDeclInitializer> ForStatDeclInitializer::Create(
    std::shared_ptr<VariableDeclaration> variableDeclaration,
    std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<ForStatDeclInitializer>(
      new ForStatDeclInitializer(variableDeclaration, location));
}

ForStatDeclInitializer::~ForStatDeclInitializer() {
}
}  // namespace ast
}  // namespace comp
