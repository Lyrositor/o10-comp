#include <comp/exceptions.h>

namespace comp {

Exception::Exception(const std::string &message) : runtime_error(message) {
}

Exception::~Exception() {
}

CompileException::CompileException(
  const std::string &message,
  const std::shared_ptr<ast::SourceLocation> location
) : Exception(message), location_(location) {
}

CompileException::~CompileException() {
}

std::shared_ptr<ast::SourceLocation> CompileException::GetLocation() const {
  return location_;
}

ParserException::ParserException(
  const std::string &message,
  const std::shared_ptr<ast::SourceLocation> location
) : CompileException(message, location) {
}

ParserException::~ParserException() {
}
}  // namespace comp
