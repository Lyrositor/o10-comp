#include <comp/as/ast.h>
#include <comp/as/emit.h>
#include "gtest/gtest.h"

namespace comp {
namespace as {
TEST(comp__as__emit, DiscriminantProgram) {
  std::vector<std::shared_ptr<ast::Statement>> body;

  // .text
  body.push_back(ast::TextDirective::Create());
  // .global main
  body.push_back(ast::GlobalDirective::Create(ast::GlobalSymbol::Create("main")));
  //.align 16, 0x90
  body.push_back(ast::AlignDirective::Create(ast::IntegerLiteral::Create(16), ast::IntegerLiteral::Create(0x90)));
  // .type main STT_FUNC
  body.push_back(ast::TypeDirective::Create(ast::GlobalSymbol::Create("main"), ast::TypeDescriptor::Function));
  // main:
  body.push_back(ast::EmptyStatement::Create({ast::GlobalSymbol::Create("main")}));
  // .cfi_startproc
  body.push_back(ast::CfiStartprocDirective::Create());
  // movq	$-23, %rax
  body.push_back(
    ast::Instruction::Create(
      ast::Mnemonic::Create("movq"),
      {
        ast::ImmediateOperand::Create(-23),
        ast::RegisterOperand::Create("rax")
      }
    )
  );
  // retq
  body.push_back(ast::Instruction::Create(ast::Mnemonic::Create("retq"), {}));
  // .size main, . - main
  body.push_back(
    ast::SizeDirective::Create(
      ast::GlobalSymbol::Create("main"),
      ast::BinaryExpression::Create(
        ast::BinaryOperator::Subtraction,
        ast::CurrentAddress::Create(),
        ast::GlobalSymbol::Create("main")
      )
    )
  );
  // .cfi_endproc
  body.push_back(ast::CfiEndprocDirective::Create());

  std::shared_ptr<ast::Program> program = ast::Program::Create(body);

  std::stringstream expected;
  expected << ""
    << "/* o10 compiler */\n";

  std::stringstream actual;
  emitProgram(*program, actual);

  EXPECT_EQ(expected.str(), actual.str());
}
}
}
