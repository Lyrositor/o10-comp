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

UnexpectedNodeType::UnexpectedNodeType(
  const std::string &node,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Unexpected node type") + ": '" + node, location),
    node_(node) {
}

UnexpectedNodeValue::UnexpectedNodeValue(
  const std::string &value,
  const std::string &node,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Unexpected node value") + ": '" + node + " '" + value, location),
    value_(value),
    node_(node) {
}

MismatchedTypesLeftRight::MismatchedTypesLeftRight(
  const std::string &left,
  const std::string &right,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Mismatched types for left and right operands") + ": '" + left + ", " + right, location),
    left_(left),
    right_(right) {
}

FunctionAlreadyDefined::FunctionAlreadyDefined(
  const std::string &function,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Function already defined") + ": '" + function, location),
    function_(function) {
}

FunctionAlreadyDeclared::FunctionAlreadyDeclared(
  const std::string &function,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Function already declared") + ": '" + function, location),
    function_(function) {
}

FunctionParameterListDoesNotMatch::FunctionParameterListDoesNotMatch(
  const std::string &function,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Function's parameter list does not match the declared list") + ": '" + function, location),
    function_(function) {
}

FunctionReturnTypeDoesNotMatch::FunctionReturnTypeDoesNotMatch(
  const std::string &function,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Function's return type does not match the declared type") + ": '" + function, location),
    function_(function) {
}

FunctionParameterTypeDoesNotMatch::FunctionParameterTypeDoesNotMatch(
  const std::string &function,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Function's parameter type does not match the declared type") + ": '" + function, location),
    function_(function) {
}
}  // namespace comp
