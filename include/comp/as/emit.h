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
void emitProgram(const ast::Program &node, std::ostream &out);

void emitStatement(const ast::Statement &node, std::ostream &out);

void emitAlignDirective(const ast::AlignDirective &node, std::ostream &out);

void emitCfiDefCfaOffsetDirective(const ast::CfiDefCfaOffsetDirective &node, std::ostream &out);

void emitCfiEndprocDirective(const ast::CfiEndprocDirective &node, std::ostream &out);

void emitCfiOffsetDirective(const ast::CfiOffsetDirective &node, std::ostream &out);

void emitCfiStartprocDirective(const ast::CfiStartprocDirective &node, std::ostream &out);

void emitEmptyStatement(const ast::EmptyStatement &node, std::ostream &out);

void emitGlobalDirective(const ast::GlobalDirective &node, std::ostream &out);

void emitInstruction(const ast::Instruction &node, std::ostream &out);

void emitSizeDirective(const ast::SizeDirective &node, std::ostream &out);

void emitTextDirective(const ast::TextDirective &node, std::ostream &out);

void emitTypeDirective(const ast::TypeDirective &node, std::ostream &out);

void emitExpression(const ast::Expression &node, std::ostream &out);

void emitSymbol(const ast::Symbol &node, std::ostream &out);

void emitGlobalSymbol(const ast::GlobalSymbol &node, std::ostream &out);

void emitLocalSymbol(const ast::LocalSymbol &node, std::ostream &out);

void emitBigIntegerLiteral(const ast::BigIntegerLiteral &node, std::ostream &out);

void emitBinaryExpression(const ast::BinaryExpression &node, std::ostream &out);

void emitCurrentAddress(const ast::CurrentAddress &node, std::ostream &out);

void emitIntegerLiteral(const ast::IntegerLiteral &node, std::ostream &out);

void emitMnemonic(const ast::Mnemonic &node, std::ostream &out);

void emitOperand(const ast::Operand &node, std::ostream &out);

void emitImmediateOperand(const ast::ImmediateOperand &node, std::ostream &out);

void emitRegisterOperand(const ast::RegisterOperand &node, std::ostream &out);
}
}
