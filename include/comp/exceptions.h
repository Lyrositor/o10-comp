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
  static std::string PrintLocation(const std::shared_ptr<ast::SourceLocation>);

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
    const std::string &nodeType,
    const std::shared_ptr<ast::SourceLocation> location);

  std::string GetNodeType() const;

 private:
  const std::string nodeType_;

};

class UnexpectedNodeValueError : public SyntaxException {
 public:
  UnexpectedNodeValueError(
    const std::string &node,
    const std::shared_ptr<ast::SourceLocation> location);

  UnexpectedNodeValueError(
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
    const std::shared_ptr<ast::SourceLocation> location);

};

class ArrayLengthNotLiteralError : public SyntaxException {
 public:
  ArrayLengthNotLiteralError(
    const std::string &lengthType,
    const std::shared_ptr<ast::SourceLocation> location);
  std::string GetLengthType() const;
 private:
  const std::string lengthType_;
};

class CannotSpecifySizeError : public SyntaxException {
 public:
  CannotSpecifySizeError(
    const std::shared_ptr<ast::SourceLocation> location);
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
