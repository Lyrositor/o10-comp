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

class UnexpectedNodeType : public CompilationException {
 public:
  UnexpectedNodeType(
    const std::string &node,
    const std::shared_ptr<ast::SourceLocation> location);

  std::string GetNode() const;

 private:
  const std::string node_;
};

class UnexpectedNodeValue : public CompilationException {
 public:
  UnexpectedNodeValue(
    const std::string &value,
    const std::string &node,
    const std::shared_ptr<ast::SourceLocation> location);

  std::string GetNode() const;
  std::string GetValue() const;

 private:
  const std::string node_;
  const std::string value_;
};

class MismatchedTypesLeftRight : public CompilationException {
 public:
  MismatchedTypesLeftRight(
      const std::string &left,
      const std::string &right,
      const std::shared_ptr<ast::SourceLocation> location);

  std::string GetLeft() const;
  std::string GetRight() const;

 private:
  const std::string left_;
  const std::string right_;
};

class FunctionAlreadyDefined : public CompilationException {
 public:
  FunctionAlreadyDefined(
    const std::string &function,
    const std::shared_ptr<ast::SourceLocation> location);
 private:
  const std::string function_;
};

class FunctionAlreadyDeclared : public CompilationException {
 public:
  FunctionAlreadyDeclared(
    const std::string &function,
    const std::shared_ptr<ast::SourceLocation> location);
 private:
  const std::string function_;
};

class FunctionParameterListDoesNotMatch : public CompilationException {
 public:
  FunctionParameterListDoesNotMatch(
    const std::string &function,
    const std::shared_ptr<ast::SourceLocation> location);
 private:
  const std::string function_;
};

class FunctionReturnTypeDoesNotMatch : public CompilationException {
 public:
  FunctionReturnTypeDoesNotMatch(
    const std::string &function,
    const std::shared_ptr<ast::SourceLocation> location);
 private:
  const std::string function_;
};

class FunctionParameterTypeDoesNotMatch : public CompilationException {
 public:
  FunctionParameterTypeDoesNotMatch(
      const std::string &function,
      const std::shared_ptr<ast::SourceLocation> location);
 private:
  const std::string function_;
};
}  // namespace comp
