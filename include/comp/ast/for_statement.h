#pragma once

#include <memory>

#include "comp/ast/statement.h"
#include "comp/ast/expression.h"
#include "comp/ast/variable_declaration.h"
#include "comp/ast/node.h"

namespace comp {
namespace ast {

/**
 * Abstract `for` initializer. Represents either an expression or variable
 * declaration.
 */
struct ForInitializer : public Node {
  ForInitializer(
      Type initializerType,
      std::shared_ptr<SourceLocation> location = nullptr);

  virtual ~ForInitializer() = 0;
};

struct ExpressionForInitializer final : public ForInitializer {
  static std::unique_ptr<ExpressionForInitializer> Create(
      std::shared_ptr<RExpression> expression,
      std::shared_ptr<SourceLocation> location = nullptr);

  ExpressionForInitializer(
      std::shared_ptr<RExpression> expression,
      std::shared_ptr<SourceLocation> location = nullptr);

  ~ExpressionForInitializer();

  const std::shared_ptr<RExpression> expression;
};


struct DeclarationForInitializer final : public ForInitializer {
  static std::unique_ptr<DeclarationForInitializer> Create(
      std::shared_ptr<VariableDeclaration> declaration,
      std::shared_ptr<SourceLocation> location = nullptr);
  DeclarationForInitializer(
      std::shared_ptr<VariableDeclaration> declaration,
      std::shared_ptr<SourceLocation> location = nullptr);

  ~DeclarationForInitializer();

  const std::shared_ptr<VariableDeclaration> declaration;
};

struct ForStatement final : public Statement {
  static std::unique_ptr<ForStatement> Create(
    std::shared_ptr<ForInitializer> initializer,
    std::shared_ptr<RExpression> test,
    std::shared_ptr<RExpression> update,
    std::shared_ptr<Statement> body,
    std::shared_ptr<SourceLocation> location = nullptr);

  ForStatement(
    std::shared_ptr<ForInitializer> initializer,
    std::shared_ptr<RExpression> condition,
    std::shared_ptr<RExpression> update,
    std::shared_ptr<Statement> body,
    std::shared_ptr<SourceLocation> location = nullptr);

  ~ForStatement();

  const std::shared_ptr<ForInitializer> initializer;
  const std::shared_ptr<RExpression> test;
  const std::shared_ptr<RExpression> update;
  const std::shared_ptr<Statement> body;
};
}  // namespace ast
}  // namespace comp
