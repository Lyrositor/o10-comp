#pragma once

#include <memory>

#include "comp/ast/statement.h"
#include "comp/ast/expression.h"
#include "comp/ast/variable_declaration.h"

namespace comp {
namespace ast {

/**
 * Void structure to exploit polymorphism.
 */
struct ForStatementInitializer : public Node {
  ForStatementInitializer(
      Type initializerType,
      std::shared_ptr<SourceLocation> location = nullptr);

  ~ForStatementInitializer();
};

struct ForStatExprInitializer final : public ForStatementInitializer {
  static std::unique_ptr<ForStatExprInitializer> Create(
      std::shared_ptr<RExpression> exprInit,
      std::shared_ptr<SourceLocation> location = nullptr);

  ForStatExprInitializer(
      std::shared_ptr<RExpression> exprInit,
      std::shared_ptr<SourceLocation> location = nullptr);

  ~ForStatExprInitializer();

  const std::shared_ptr<RExpression> exprInit;
};


struct ForStatDeclInitializer final : public ForStatementInitializer {
  static std::unique_ptr<ForStatDeclInitializer> Create(
      std::shared_ptr<VariableDeclaration> variableDeclaration,
      std::shared_ptr<SourceLocation> location = nullptr);
  ForStatDeclInitializer(
      std::shared_ptr<VariableDeclaration> variableDeclaration,
      std::shared_ptr<SourceLocation> location = nullptr);

  ~ForStatDeclInitializer();

  const std::shared_ptr<VariableDeclaration> variableDeclaration;
};



struct ForStatement final : public Statement {
  static std::unique_ptr<ForStatement> Create(
    std::shared_ptr<ForStatementInitializer> initialization,
    std::shared_ptr<RExpression> condition,
    std::shared_ptr<RExpression> iteration,
    std::shared_ptr<Statement> body,
    std::shared_ptr<SourceLocation> location = nullptr);

  ForStatement(
    std::shared_ptr<ForStatementInitializer> initialization,
    std::shared_ptr<RExpression> condition,
    std::shared_ptr<RExpression> iteration,
    std::shared_ptr<Statement> body,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~ForStatement();

  const std::shared_ptr<ForStatementInitializer> initialization;
  const std::shared_ptr<RExpression> condition;
  const std::shared_ptr<RExpression> iteration;
  const std::shared_ptr<Statement> body;
};
}  // namespace ast
}  // namespace comp
