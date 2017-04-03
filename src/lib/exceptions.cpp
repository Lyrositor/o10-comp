#include <comp/exceptions.h>

#include <sstream>
#include <unordered_map>

namespace comp {

Exception::Exception(const std::string &message) : runtime_error(message) {
}

CompilationException::CompilationException(
  const std::string &message,
  const std::shared_ptr<ast::SourceLocation> location
) : Exception(message) , location_(location) {
}

std::shared_ptr<ast::SourceLocation> CompilationException::GetLocation() const {
  return location_;
}

SyntaxException::SyntaxException(
  const std::string &message,
  const std::shared_ptr<ast::SourceLocation> location
) : CompilationException(message, location) {
}

UnexpectedTokenError::UnexpectedTokenError(
  const std::string &token,
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Unexpected token") + ": '" + token + "'", location),
    token_(token) {
}

std::string UnexpectedTokenError::GetToken() const {
  return token_;
}
}  // namespace comp
