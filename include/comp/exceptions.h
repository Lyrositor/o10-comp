#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include "comp/ast/position.h"

namespace comp {
class Exception : public std::runtime_error {
 public:
  Exception(const std::string &message);

  virtual ~Exception();
};

class CompileException : public Exception {
 public:
  CompileException(
    const std::string &message,
    const std::shared_ptr<ast::SourceLocation>);

  virtual ~CompileException();

  std::shared_ptr<ast::SourceLocation> GetLocation() const;

 private:
  const std::shared_ptr<ast::SourceLocation> location_;
};

class ParserException : public CompileException {
 public:
  ParserException(
    const std::string &message,
    const std::shared_ptr<ast::SourceLocation>);

  virtual ~ParserException();
};
}  // namespace comp
