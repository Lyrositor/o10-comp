#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include "comp/ast.h"

namespace comp {
class Exception : public std::runtime_error {
 public:
  Exception(const std::string &message);
};

class CompilationException : public Exception {
 public:
  CompilationException(
    const std::string &message,
    const std::shared_ptr<ast::SourceLocation>);

  std::shared_ptr<ast::SourceLocation> GetLocation() const;

 private:
    const std::shared_ptr<ast::SourceLocation> location_;
};

class SyntaxException : public CompilationException {
 public:
  SyntaxException(
    const std::string &message,
    const std::shared_ptr<ast::SourceLocation>);
};

class UnexpectedTokenError : public SyntaxException {
 public:
  UnexpectedTokenError(
    const std::string &token,
    const std::shared_ptr<ast::SourceLocation> location);
};

class UnexpectedNodeTypeError : public SyntaxException {
 public:
  UnexpectedNodeTypeError(const ast::Node &node);
};

class UnexpectedBinaryOperatorError : public SyntaxException {
 public:
  UnexpectedBinaryOperatorError(const ast::BinaryExpression &op);
};

class MismatchedTypesLeftRightError : public CompilationException {
 public:
  MismatchedTypesLeftRightError(
    const std::string &left,
    const std::string &right,
    const std::shared_ptr<ast::SourceLocation> location);
};

class FunctionAlreadyDefinedError : public CompilationException {
 public:
  FunctionAlreadyDefinedError(const ast::Function &function);
};

class FunctionAlreadyDeclaredError : public CompilationException {
 public:
  FunctionAlreadyDeclaredError(const ast::Function &function);
};

class FunctionParameterListDoesNotMatchError : public CompilationException {
 public:
  FunctionParameterListDoesNotMatchError(const ast::Function &function);
};

class FunctionReturnTypeDoesNotMatchError : public CompilationException {
 public:
  FunctionReturnTypeDoesNotMatchError(const ast::Function &function);
};

class FunctionParameterTypeDoesNotMatchError : public CompilationException {
 public:
  FunctionParameterTypeDoesNotMatchError(const ast::Parameter &parameter);
};

class ArrayLengthNotLiteralError : public SyntaxException {
 public:
  ArrayLengthNotLiteralError(const ast::ArrayDataType &data_type);
};

class CannotSpecifySizeError : public SyntaxException {
 public:
  CannotSpecifySizeError(const std::shared_ptr<ast::SourceLocation> location);
};

class InvalidIdentifierError : public SyntaxException {
 public:
  InvalidIdentifierError(const ast::Identifier &identifier);
};
}  // namespace comp
