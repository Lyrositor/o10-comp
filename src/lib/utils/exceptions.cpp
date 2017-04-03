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

std::string CompilationException::PrintLocation(const std::shared_ptr<comp::ast::SourceLocation> location){
  std::stringstream msg;
  //size_t a1=location->start.line;
  //int b1;
  //b1 = (int)a1;
  //size_t a2=location->start.line;
  //int b2;
  //b2 = (int)a2;
  msg << "at line " <<  ", column "  << ".";
  return msg.str();
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
    std::string("Unexpected token") + ": '" + token + "'"
      + CompilationException::PrintLocation(location),
    location),
    token_(token) {
}

std::string UnexpectedTokenError::GetToken() const {
  return token_;
}

UnexpectedNodeTypeError::UnexpectedNodeTypeError(
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Unexpected node type")
      + CompilationException::PrintLocation(location),
    location){
}


UnexpectedNodeValueError::UnexpectedNodeValueError(
  const std::string &node,
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Unexpected node value") + ": '" + node + "'"
      + CompilationException::PrintLocation(location),
    location),
    node_(node) {
}

std::string UnexpectedNodeValueError::GetNode() const {
  return node_;
}

MismatchedTypesLeftRightError::MismatchedTypesLeftRightError(
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Mismatched types for left and right operands")
      + CompilationException::PrintLocation(location),
    location){
}

FunctionAlreadyDefinedError::FunctionAlreadyDefinedError(
  const std::string &function,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("Function already defined")
      + ": '" + function + "'" + CompilationException::PrintLocation(location),
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
    std::string("Function already declared")
      + ": '" + function + "'" + CompilationException::PrintLocation(location),
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
      + CompilationException::PrintLocation(location),
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
      + CompilationException::PrintLocation(location),
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
      + CompilationException::PrintLocation(location),
    location),
    function_(function) {
}

std::string FunctionParameterTypeDoesNotMatchError::GetFunction() const {
  return function_;
}

UnexpectedNodeTypeInRootError::UnexpectedNodeTypeInRootError(
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Unexpected node type in root context."), location){
}

ArrayLengthNotLiteralError::ArrayLengthNotLiteralError(
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Array length not a literal") + CompilationException::PrintLocation(location),
    location){
}

CannotSpecifySizeError::CannotSpecifySizeError(
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Cannot specify size")
      + CompilationException::PrintLocation(location),
    location){
}

InvalidIdentifierError::InvalidIdentifierError(
  const std::string &identifier,
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Cannot specify size") + ": '" + identifier + "'"
      + CompilationException::PrintLocation(location),
    location),
  identifier_(identifier) {
}

std::string InvalidIdentifierError::GetIdentifier() const {
  return identifier_;
}


}  // namespace comp
