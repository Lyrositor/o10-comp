#include <comp/utils/exceptions.h>

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
  SyntaxException("Unexpected token: '" + token + "'", location) {
}

UnexpectedNodeTypeError::UnexpectedNodeTypeError(const ast::Node &node) :
  SyntaxException(
    "Unexpected node type: '" + ast::Node::ToString(node.node_type) + "'",
    node.location) {
}

UnexpectedBinaryOperatorError::UnexpectedBinaryOperatorError(
  const ast::BinaryExpression &op) :
  SyntaxException(
    "unexpected binary operator: '" + ast::BinaryOperatorToString(op.op) + "'",
    op.location) {
}

MismatchedTypesLeftRightError::MismatchedTypesLeftRightError(
  const std::string &left,
  const std::string &right,
  const std::shared_ptr<ast::SourceLocation> location
) :
  CompilationException(
    std::string("mismatched types for left and right operands: '")
      + left + "','" + right + "'",
    location) {
}

FunctionAlreadyDefinedError::FunctionAlreadyDefinedError(
  const ast::Function &function
) :
  CompilationException(
    "function already defined: '" + function.identifier->name + "'",
    function.identifier->location) {
}

FunctionAlreadyDeclaredError::FunctionAlreadyDeclaredError(
  const ast::Function &function) :
  CompilationException(
    "function already declared: '" + function.identifier->name + "'",
    function.identifier->location) {
}

FunctionParameterListDoesNotMatchError::FunctionParameterListDoesNotMatchError(
  const ast::Function &function) :
  CompilationException(
    "function's defined parameter list does not match the declared list: '"
      + function.identifier->name + "'",
    ast::SourceLocation::Create(
      function.identifier->location->end,
      function.body->location->start)) {
}

FunctionReturnTypeDoesNotMatchError::FunctionReturnTypeDoesNotMatchError(
  const ast::Function &function
) :
  CompilationException(
    "function's defined return type does not match the declared type",
    function.return_type->location) {
}

FunctionParameterTypeDoesNotMatchError::FunctionParameterTypeDoesNotMatchError(
  const ast::Parameter &parameter
) :
  CompilationException(
    "function's defined parameter type does not match the declared type",
    parameter.location) {
}

ArrayLengthNotLiteralError::ArrayLengthNotLiteralError(
  const ast::ArrayDataType &data_type
) :
  SyntaxException(
    "array length not a literal: '"
      + ast::Node::ToString(data_type.size->node_type) + "'",
    data_type.size->location) {
}

CannotSpecifySizeError::CannotSpecifySizeError(
  const std::shared_ptr<ast::SourceLocation> location
) :
  SyntaxException(
    std::string("cannot specify size of array"),
    location) {
}

InvalidIdentifierError::InvalidIdentifierError(
  const ast::Identifier &identifier
) :
  SyntaxException(
    "invalid identifier: '" + identifier.name + "'",
    identifier.location) {
}
}  // namespace comp
