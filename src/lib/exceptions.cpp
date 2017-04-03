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
    std::string("Unexpected token") + ": '" + token + "'" + " at line " +
      std::to_string(location->start.line) + ", column " + std::to_string(location->start.column) + ".",
    location),
    token_(token) {
}

std::string UnexpectedTokenError::GetToken() const {
  return token_;
}

UnexpectedNodeTypeError::UnexpectedNodeTypeError(
  const std::string &node,
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Unexpected node type") + ": '" + node + "'" + " at line " +
      std::to_string(location->start.line) + ", column " + std::to_string(location->start.column) + ".",
    location),
    node_(node) {
}

std::string UnexpectedNodeTypeError::GetNode() const {
  return node_;
}

UnexpectedNodeValueError::UnexpectedNodeValueError(
  const std::string &node,
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Unexpected node value") + ": '" + node + "'" + " at line " +
      std::to_string(location->start.line) + ", column " + std::to_string(location->start.column) + ".",
    location),
    node_(node) {
}

std::string UnexpectedNodeValueError::GetNode() const {
  return node_;
}

MismatchedTypesLeftRightError::MismatchedTypesLeftRightError(
  const std::string &left,
  const std::string &right,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Mismatched types for left and right operands") + ": '" + left + ", " + right + "'"
      + " at line " + std::to_string(location->start.line)
      + ", column " + std::to_string(location->start.column) + ".",
    location),
    left_(left),
    right_(right) {
}

std::string MismatchedTypesLeftRightError::GetLeft() const {
  return left_;
}

std::string MismatchedTypesLeftRightError::GetRight() const {
  return right_;
}

FunctionAlreadyDefinedError::FunctionAlreadyDefinedError(
  const std::string &function,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Function already defined") + ": '" + function + "'" + " at line " +
      std::to_string(location->start.line) + ", column " + std::to_string(location->start.column) + ".",
    location),
    function_(function) {
}

std::string FunctionAlreadyDefinedError::GetFunction() const {
  return function_;
}

FunctionAlreadyDeclaredError::FunctionAlreadyDeclaredError(
  const std::string &function,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Function already declared") + ": '" + function + "'" + " at line " +
      std::to_string(location->start.line) + ", column " + std::to_string(location->start.column) + ".",
    location),
    function_(function) {
}

std::string FunctionAlreadyDeclaredError::GetFunction() const {
  return function_;
}

FunctionParameterListDoesNotMatchError::FunctionParameterListDoesNotMatchError(
  const std::string &function,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Function's parameter list does not match the declared list") + ": '" + function + "'"
      + " at line " + std::to_string(location->start.line)
      + ", column " + std::to_string(location->start.column) + ".",
    location),
    function_(function) {
}

std::string FunctionParameterListDoesNotMatchError::GetFunction() const {
  return function_;
}

FunctionReturnTypeDoesNotMatchError::FunctionReturnTypeDoesNotMatchError(
  const std::string &function,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Function's return type does not match the declared type") + ": '" + function + "'"
      + " at line " + std::to_string(location->start.line)
      + ", column " + std::to_string(location->start.column) + ".",
    location),
    function_(function) {
}

std::string FunctionReturnTypeDoesNotMatchError::GetFunction() const {
  return function_;
}

FunctionParameterTypeDoesNotMatchError::FunctionParameterTypeDoesNotMatchError(
  const std::string &function,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Function's parameter type does not match the declared type") + ": '" + function + "'"
      + " at line " + std::to_string(location->start.line)
      + ", column " + std::to_string(location->start.column) + ".",
    location),
    function_(function) {
}

std::string FunctionParameterTypeDoesNotMatchError::GetFunction() const {
  return function_;
}

UnexpectedNodeTypeInRootError::UnexpectedNodeTypeInRootError(
  const std::string &node,
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Unexpected node type in root context") + ": '" + node + "'" + " at line " +
      std::to_string(location->start.line) + ", column " + std::to_string(location->start.column) + ".",
    location),
  node_(node) {
}

std::string UnexpectedNodeTypeInRootError::GetNode() const {
  return node_;
}

ArrayLengthNotLiteralError::ArrayLengthNotLiteralError(
  const std::string &array,
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Array length not a literal") + ": '" + array + "'" + " at line " +
      std::to_string(location->start.line) + ", column " + std::to_string(location->start.column) + ".",
    location),
  array_(array) {
}

std::string ArrayLengthNotLiteralError::GetArray() const {
  return array_;
}

CannotSpecifySizeError::CannotSpecifySizeError(
  const std::string &array,
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Cannot specify size") + ": '" + array + "'" + " at line " +
      std::to_string(location->start.line) + ", column " + std::to_string(location->start.column) + ".",
    location),
  array_(array) {
}

std::string CannotSpecifySizeError::GetArray() const {
  return array_;
}

InvalidIdentifierError::InvalidIdentifierError(
  const std::string &identifier,
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Cannot specify size") + ": '" + identifier + "'" + " at line " +
      std::to_string(location->start.line) + ", column " + std::to_string(location->start.column) + ".",
    location),
  identifier_(identifier) {
}

std::string InvalidIdentifierError::GetIdentifier() const {
  return identifier_;
}


}  // namespace comp
