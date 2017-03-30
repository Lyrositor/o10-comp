#pragma once

#include <ostream>
#include "comp/as/ast.h"

namespace comp {
namespace as {
/**
 * Serialize the provided `node` and write it to `out`.
 *
 * The generated assembly code will use the AT&T syntax.
 */
void EmitProgram(const ast::Program &node, std::ostream &out);

void EmitStatement(const ast::Statement &node, std::ostream &out);

void EmitAlignDirective(const ast::AlignDirective &node, std::ostream &out);

void EmitCfiDefCfaOffsetDirective(const ast::CfiDefCfaOffsetDirective &node, std::ostream &out);

void EmitCfiEndprocDirective(const ast::CfiEndprocDirective &node, std::ostream &out);

void EmitCfiOffsetDirective(const ast::CfiOffsetDirective &node, std::ostream &out);

void EmitCfiStartprocDirective(const ast::CfiStartprocDirective &node, std::ostream &out);

void EmitEmptyStatement(const ast::EmptyStatement &node, std::ostream &out);

void EmitGlobalDirective(const ast::GlobalDirective &node, std::ostream &out);

void EmitInstruction(const ast::Instruction &node, std::ostream &out);

void EmitSizeDirective(const ast::SizeDirective &node, std::ostream &out);

void EmitTextDirective(const ast::TextDirective &node, std::ostream &out);

void EmitTypeDirective(const ast::TypeDirective &node, std::ostream &out);

void EmitExpression(const ast::Expression &node, std::ostream &out);

void EmitSymbol(const ast::Symbol &node, std::ostream &out);

void EmitGlobalSymbol(const ast::GlobalSymbol &node, std::ostream &out);

void EmitLocalSymbol(const ast::LocalSymbol &node, std::ostream &out);

void EmitBigIntegerLiteral(const ast::BigIntegerLiteral &node, std::ostream &out);

void EmitBinaryExpression(const ast::BinaryExpression &node, std::ostream &out);

void EmitCurrentAddress(const ast::CurrentAddress &node, std::ostream &out);

void EmitIntegerLiteral(const ast::IntegerLiteral &node, std::ostream &out);

void EmitMnemonic(const ast::Mnemonic &node, std::ostream &out);

void EmitOperand(const ast::Operand &node, std::ostream &out);

void EmitImmediateOperand(const ast::ImmediateOperand &node, std::ostream &out);

void EmitRegisterOperand(const ast::RegisterOperand &node, std::ostream &out);
}
}
