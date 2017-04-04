#include <comp/ast/for_statement.h>
#include <comp/ast.h>

namespace comp {
namespace ast {
// ForStatementInitializer
ForInitializer::ForInitializer(
    Type initializerType,
    std::shared_ptr<SourceLocation> location
) :
    Node(initializerType,location) {
}
ForInitializer::~ForInitializer() {
}

// ExpressionForInitializer
std::unique_ptr<ExpressionForInitializer> ExpressionForInitializer::Create(
  std::shared_ptr<RExpression> expression,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<ExpressionForInitializer>(
    new ExpressionForInitializer(expression, location));
}

ExpressionForInitializer::ExpressionForInitializer(
    std::shared_ptr<RExpression> expression,
    std::shared_ptr<SourceLocation> location
) :
    ForInitializer(Type::ExpressionForInitializer, location),
    expression(expression) {
}

ExpressionForInitializer::~ExpressionForInitializer() {
}

// DeclarationForInitializer
std::unique_ptr<DeclarationForInitializer> DeclarationForInitializer::Create(
  std::shared_ptr<VariableDeclaration> declaration,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<DeclarationForInitializer>(
    new DeclarationForInitializer(declaration, location));
}

DeclarationForInitializer::DeclarationForInitializer(
    std::shared_ptr<VariableDeclaration> declaration,
    std::shared_ptr<SourceLocation> location
) :
    ForInitializer(Type::DeclarationForInitializer, location),
    declaration(declaration) {
}

DeclarationForInitializer::~DeclarationForInitializer() {
}

// ForStatement
std::unique_ptr<ForStatement> ForStatement::Create(
  std::shared_ptr<ForInitializer> initialization,
  std::shared_ptr<RExpression> test,
  std::shared_ptr<RExpression> update,
  std::shared_ptr<Statement> body,
  std::shared_ptr<SourceLocation> location
) {
  return std::unique_ptr<ForStatement>(
    new ForStatement(initialization, test, update, body, location));
}

ForStatement::ForStatement(
  std::shared_ptr<ForInitializer> initializer,
  std::shared_ptr<RExpression> test,
  std::shared_ptr<RExpression> update,
  std::shared_ptr<Statement> body,
  std::shared_ptr<SourceLocation> location
) :
  Statement(Type::ForStatement, location),
  initializer(initializer),
  test(test),
  update(update),
  body(body) {
}

ForStatement::~ForStatement() {
}
}  // namespace ast
}  // namespace comp
