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
  if (location == nullptr) {
    msg << "at unknown location.";
  }else{
    size_t a1=location->start.line;
    int b1;
    b1 = (int)a1;
    size_t a2=location->start.line;
    int b2;
    b2 = (int)a2;
    msg << "at line " << b1 <<  ", column "  << b2 << ".";
  }
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
  const std::string &nodeType,
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Unexpected node type") + ": '" + nodeType + "'"
      + CompilationException::PrintLocation(location),
    location),
    nodeType_(nodeType){
}

std::string UnexpectedNodeTypeError::GetNodeType() const {
  return nodeType_;
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

UnexpectedNodeValueError::UnexpectedNodeValueError(
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Unexpected node value")
      + CompilationException::PrintLocation(location),
    location) {
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
    std::string("Mismatched types for left and right operands") + ": '" + left + "','" + right + "'"
      + CompilationException::PrintLocation(location),
    location),
    left_(left),right_(right){
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
    std::string("Unexpected node type in root context."),
    location){
}

ArrayLengthNotLiteralError::ArrayLengthNotLiteralError(
  const std::string &lengthType,
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Array length not a literal")  + ": '" + lengthType + "'"
      + CompilationException::PrintLocation(location),
    location),
  lengthType_(lengthType){
}

std::string ArrayLengthNotLiteralError::GetLengthType() const {
  return lengthType_;
}

CannotSpecifySizeError::CannotSpecifySizeError(
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Cannot specify size of array")
      + CompilationException::PrintLocation(location),
    location){
}

InvalidIdentifierError::InvalidIdentifierError(
  const std::string &identifier,
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("Invalid identifier") + ": '" + identifier + "'"
      + CompilationException::PrintLocation(location),
    location),
  identifier_(identifier) {
}

std::string InvalidIdentifierError::GetIdentifier() const {
  return identifier_;
}


}  // namespace comp
