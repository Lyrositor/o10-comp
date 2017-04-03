#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include "comp/ast/position.h"

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

  std::string GetToken() const;

 private:
  const std::string token_;
};

class UnexpectedNodeTypeError : public SyntaxException {
 public:
  UnexpectedNodeTypeError(
    const std::string &node,
    const std::shared_ptr<ast::SourceLocation> location);

  std::string GetNode() const;

 private:
  const std::string node_;
};

class UnexpectedNodeValueError : public SyntaxException {
 public:
  UnexpectedNodeValueError(
    const std::string &node,
    const std::shared_ptr<ast::SourceLocation> location);

  std::string GetNode() const;

 private:
  const std::string node_;
};

class MismatchedTypesLeftRightError : public CompilationException {
 public:
  MismatchedTypesLeftRightError(
      const std::string &left,
      const std::string &right,
      const std::shared_ptr<ast::SourceLocation> location);

  std::string GetLeft() const;
  std::string GetRight() const;

 private:
  const std::string left_;
  const std::string right_;
};

class FunctionAlreadyDefinedError : public CompilationException {
 public:
  FunctionAlreadyDefinedError(
    const std::string &function,
    const std::shared_ptr<ast::SourceLocation> location);
  std::string GetFunction() const;
 private:
  const std::string function_;
};

class FunctionAlreadyDeclaredError : public CompilationException {
 public:
  FunctionAlreadyDeclaredError(
    const std::string &function,
    const std::shared_ptr<ast::SourceLocation> location);
  std::string GetFunction() const;
 private:
  const std::string function_;
};

class FunctionParameterListDoesNotMatchError : public CompilationException {
 public:
  FunctionParameterListDoesNotMatchError(
    const std::string &function,
    const std::shared_ptr<ast::SourceLocation> location);
  std::string GetFunction() const;
 private:
  const std::string function_;
};

class FunctionReturnTypeDoesNotMatchError : public CompilationException {
 public:
  FunctionReturnTypeDoesNotMatchError(
    const std::string &function,
    const std::shared_ptr<ast::SourceLocation> location);
  std::string GetFunction() const;
 private:
  const std::string function_;
};

class FunctionParameterTypeDoesNotMatchError : public CompilationException {
 public:
  FunctionParameterTypeDoesNotMatchError(
    const std::string &function,
    const std::shared_ptr<ast::SourceLocation> location);
  std::string GetFunction() const;
 private:
  const std::string function_;
};

class UnexpectedNodeTypeInRootError : public SyntaxException {
 public:
  UnexpectedNodeTypeInRootError(
    const std::string &node,
    const std::shared_ptr<ast::SourceLocation> location);

  std::string GetNode() const;

 private:
  const std::string node_;
};

class ArrayLengthNotLiteralError : public SyntaxException {
 public:
  ArrayLengthNotLiteralError(
    const std::string &array,
    const std::shared_ptr<ast::SourceLocation> location);

  std::string GetArray() const;

 private:
  const std::string array_;
};

class CannotSpecifySizeError : public SyntaxException {
 public:
  CannotSpecifySizeError(
    const std::string &array,
    const std::shared_ptr<ast::SourceLocation> location);

  std::string GetArray() const;

 private:
  const std::string array_;
};


class InvalidIdentifierError : public SyntaxException {
 public:
  InvalidIdentifierError(
    const std::string &identifier,
    const std::shared_ptr<ast::SourceLocation> location);

  std::string GetIdentifier() const;

 private:
  const std::string identifier_;
};


}  // namespace comp
