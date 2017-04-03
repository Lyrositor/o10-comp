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
}  // namespace comp
