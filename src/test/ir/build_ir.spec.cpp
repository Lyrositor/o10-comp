#include "gtest/gtest.h"

#include <comp/ir/build_ir.h>

namespace comp {
namespace ir {
TEST(comp__ir__build_ir, buildProgramIR) {
  // Create a function declaration
  std::shared_ptr<ast::Function> function_decl_node = ast::Function::Create(
    ast::Identifier::Create("foo"),
    {},
    ast::IdentifierDataType::Create(ast::Identifier::Create("void")),
    nullptr);

  // Create a function definition matching the declaration's signature
  std::shared_ptr<ast::Function> function_def_node = ast::Function::Create(
    ast::Identifier::Create("foo"),
    {},
    ast::IdentifierDataType::Create(ast::Identifier::Create("void")),
    ast::BlockStatement::Create({}));

  // Create a function definition which does not match the declaration's
  // signature
  std::shared_ptr<ast::Function> function_def_node_bad = ast::Function::Create(
    ast::Identifier::Create("foo"),
    {},
    ast::IdentifierDataType::Create(ast::Identifier::Create("int64_t")),
    ast::BlockStatement::Create({}));

  // Create the various program variations
  std::shared_ptr<const ast::Program> program_node_no_decl =
    ast::Program::Create({function_def_node});
  std::shared_ptr<const ast::Program> program_node_with_decl =
    ast::Program::Create({function_decl_node, function_def_node});
  std::shared_ptr<const ast::Program> program_node_wrong_order =
    ast::Program::Create({function_def_node, function_decl_node});
  std::shared_ptr<const ast::Program> program_node_double_def =
    ast::Program::Create({function_def_node, function_def_node});
  std::shared_ptr<const ast::Program> program_node_double_decl =
    ast::Program::Create({function_decl_node, function_decl_node});
  std::shared_ptr<const ast::Program> program_node_bad_sig =
    ast::Program::Create({function_decl_node, function_def_node_bad});

  ASSERT_NO_THROW(BuildProgramIR(*program_node_no_decl));
  ASSERT_NO_THROW(BuildProgramIR(*program_node_with_decl));
  ASSERT_THROW(BuildProgramIR(*program_node_wrong_order), std::runtime_error);
  ASSERT_THROW(BuildProgramIR(*program_node_double_def), std::runtime_error);
  ASSERT_THROW(BuildProgramIR(*program_node_double_decl), std::runtime_error);
  ASSERT_THROW(BuildProgramIR(*program_node_bad_sig), std::runtime_error);
}

TEST(comp__ir__build_ir, buildFunctionIR) {
  std::shared_ptr<ast::Identifier> identifier = ast::Identifier::Create("foo");
  std::vector<std::shared_ptr<ast::Parameter>> parameters = {
    ast::NamedParameter::Create(
      ast::IdentifierDataType::Create(ast::Identifier::Create("int32_t")),
      ast::IdentifierDeclarator::Create(ast::Identifier::Create("bar1"))),
    ast::NamedParameter::Create(
      ast::IdentifierDataType::Create(ast::Identifier::Create("int32_t")),
      ast::IdentifierDeclarator::Create(ast::Identifier::Create("bar2")))
  };
  std::shared_ptr<ast::DataType> return_type = ast::IdentifierDataType::Create(
    ast::Identifier::Create("int64_t"));

  std::shared_ptr<ast::BlockStatement> body = ast::BlockStatement::Create(
    {
      ast::ReturnStatement::Create(
        ast::BinaryExpression::Create(
          ast::BinaryOperator::Addition,
          ast::Identifier::Create("bar1"),
          ast::Identifier::Create("bar2")
        )
      )
    });

  ASSERT_NO_THROW(std::shared_ptr<ast::Function> function_node =
    ast::Function::Create(identifier, parameters, return_type, body));
}
}  // namespace ir
}  // namespace comp
