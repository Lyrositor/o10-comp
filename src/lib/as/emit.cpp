#include <comp/as/emit.h>
#include <comp/ast.h>
#include <comp/as/ast.h>

namespace comp {
namespace as {
void EmitProgram(const ast::Program &node, std::ostream &out) {
  for (auto statement : node.body) {
    EmitStatement(*statement, out);
  }
}

void EmitStatement(const ast::Statement &node, std::ostream &out) {
  switch (node.node_type) {
    case ast::Node::Type::AlignDirective: {
      return EmitAlignDirective(static_cast<const ast::AlignDirective &>(node), out);
    }
    case ast::Node::Type::CfiEndprocDirective: {
      return EmitCfiEndprocDirective(static_cast<const ast::CfiEndprocDirective &>(node), out);
    }
    case ast::Node::Type::CfiStartprocDirective: {
      return EmitCfiStartprocDirective(static_cast<const ast::CfiStartprocDirective &>(node), out);
    }
    case ast::Node::Type::EmptyStatement: {
      return EmitEmptyStatement(static_cast<const ast::EmptyStatement &>(node), out);
    }
    case ast::Node::Type::GlobalDirective: {
      return EmitGlobalDirective(static_cast<const ast::GlobalDirective &>(node), out);
    }
    case ast::Node::Type::Instruction: {
      return EmitInstruction(static_cast<const ast::Instruction &>(node), out);
    }
    case ast::Node::Type::SizeDirective: {
      return EmitSizeDirective(static_cast<const ast::SizeDirective &>(node), out);
    }
    case ast::Node::Type::TextDirective: {
      return EmitTextDirective(static_cast<const ast::TextDirective &>(node), out);
    }
    case ast::Node::Type::TypeDirective: {
      return EmitTypeDirective(static_cast<const ast::TypeDirective &>(node), out);
    }
    default: {
      throw std::domain_error("Unexpected value for `node.node_type`");
    }
  }
}

void EmitLabels(
  const std::vector<std::shared_ptr<ast::Symbol>> &labels,
  std::ostream &out,
  bool add_trailing_space) {
  for (size_t i = 0, l = labels.size(); i < l; i++) {
    EmitSymbol(*labels[i], out);
    out << (i < l - 1 || add_trailing_space ? ": " : ":");
  }
}

void EmitAlignDirective(const ast::AlignDirective &node, std::ostream &out) {
  EmitLabels(node.labels, out, true);
  out << ".align ";
  EmitExpression(*node.alignment_value, out);
  if (node.fill_value != nullptr || node.max_skipped_bytes != nullptr) {
    out << ", ";
  }
  if (node.fill_value != nullptr) {
    EmitExpression(*node.fill_value, out);
  }
  if (node.max_skipped_bytes != nullptr) {
    out << ", ";
    EmitExpression(*node.max_skipped_bytes, out);
  }
  out << "\n";
}

void EmitCfiDefCfaOffsetDirective(const ast::CfiDefCfaOffsetDirective &node, std::ostream &out) {
  EmitLabels(node.labels, out, true);
  out << ".cfi_def_cfa_offset ";
  EmitExpression(*node.offset, out);
  out << "\n";
}

void EmitCfiEndprocDirective(const ast::CfiEndprocDirective &node, std::ostream &out) {
  EmitLabels(node.labels, out, true);
  out << ".cfi_endproc\n";
}

void EmitCfiOffsetDirective(const ast::CfiOffsetDirective &node, std::ostream &out) {
  EmitLabels(node.labels, out, true);
  out << ".cfi_offset ";
  EmitRegisterOperand(*node.reg, out);
  out << ", ";
  EmitExpression(*node.size, out);
  out << "\n";
}

void EmitCfiStartprocDirective(const ast::CfiStartprocDirective &node, std::ostream &out) {
  EmitLabels(node.labels, out, true);
  out << ".cfi_startproc\n";
}

void EmitEmptyStatement(const ast::EmptyStatement &node, std::ostream &out) {
  EmitLabels(node.labels, out, false);
  out << "\n";
}

void EmitGlobalDirective(const ast::GlobalDirective &node, std::ostream &out) {
  EmitLabels(node.labels, out, true);
  out << ".global ";
  EmitSymbol(*node.symbol, out);
  out << "\n";
}

void EmitInstruction(const ast::Instruction &node, std::ostream &out) {
  EmitLabels(node.labels, out, true);
  EmitMnemonic(*node.mnemonic, out);
  for (size_t i = 0, l = node.operands.size(); i < l; i++) {
    out << (i == 0 ? " " : ", ");
    EmitOperand(*node.operands[i], out);
  }
  out << "\n";
}

void EmitSizeDirective(const ast::SizeDirective &node, std::ostream &out) {
  EmitLabels(node.labels, out, true);
  out << ".size ";
  EmitSymbol(*node.symbol, out);
  out << ", ";
  EmitExpression(*node.size, out);
  out << "\n";
}

void EmitTextDirective(const ast::TextDirective &node, std::ostream &out) {
  EmitLabels(node.labels, out, true);
  out << ".text\n";
}

void EmitTypeDirective(const ast::TypeDirective &node, std::ostream &out) {
  EmitLabels(node.labels, out, true);
  out << ".type ";
  EmitSymbol(*node.symbol, out);
  out << " ";
  switch (node.type_descriptor) {
    case ast::TypeDescriptor::Function: {
      out << "CTT_FUNC";
      break;
    }
    default: {
      throw std::domain_error("node.type_descriptor");
    }
  }
  out << "\n";
}

void EmitExpression(const ast::Expression &node, std::ostream &out) {
  switch (node.node_type) {
    case ast::Node::Type::BigIntegerLiteral: {
      return EmitBigIntegerLiteral(static_cast<const ast::BigIntegerLiteral &>(node), out);
    }
    case ast::Node::Type::BinaryExpression: {
      return EmitBinaryExpression(static_cast<const ast::BinaryExpression &>(node), out);
    }
    case ast::Node::Type::CurrentAddress: {
      return EmitCurrentAddress(static_cast<const ast::CurrentAddress &>(node), out);
    }
    case ast::Node::Type::GlobalSymbol: {
      return EmitGlobalSymbol(static_cast<const ast::GlobalSymbol &>(node), out);
    }
    case ast::Node::Type::IntegerLiteral: {
      return EmitIntegerLiteral(static_cast<const ast::IntegerLiteral &>(node), out);
    }
    case ast::Node::Type::LocalSymbol: {
      return EmitLocalSymbol(static_cast<const ast::LocalSymbol &>(node), out);
    }
    default: {
      throw std::domain_error("Unexpected value for `node.node_type`");
    }
  }
}

void EmitSymbol(const ast::Symbol &node, std::ostream &out) {
  switch (node.node_type) {
    case ast::Node::Type::GlobalSymbol: {
      return EmitGlobalSymbol(static_cast<const ast::GlobalSymbol &>(node), out);
    }
    case ast::Node::Type::LocalSymbol: {
      return EmitLocalSymbol(static_cast<const ast::LocalSymbol &>(node), out);
    }
    default: {
      throw std::domain_error("Unexpected value for `node.node_type`");
    }
  }
}

void EmitGlobalSymbol(const ast::GlobalSymbol &node, std::ostream &out) {
  out << node.name;
}

void EmitLocalSymbol(const ast::LocalSymbol &node, std::ostream &out) {
  out << ".L" << node.name;
}

void EmitBigIntegerLiteral(const ast::BigIntegerLiteral &node, std::ostream &out) {
  if (node.value > 0) {
    out << node.value;
  } else {
    out << "(" << node.value << ")";
  }
}

std::string serializeBinaryOperator(const ast::BinaryOperator op) {
  switch (op) {
    case ast::BinaryOperator::Addition: return "+";
    case ast::BinaryOperator::BitwiseAnd: return "&";
    case ast::BinaryOperator::BitwiseOr: return "|";
    case ast::BinaryOperator::BitwiseOrNot: return "!";
    case ast::BinaryOperator::BitwiseXor: return "^";
    case ast::BinaryOperator::Division: return "/";
    case ast::BinaryOperator::Equal: return "==";
    case ast::BinaryOperator::GreaterThan: return ">";
    case ast::BinaryOperator::GreaterThanOrEqual: return ">=";
    case ast::BinaryOperator::LessThan: return "<";
    case ast::BinaryOperator::LessThanOrEqual: return "<=";
    case ast::BinaryOperator::LogicalAnd: return "&&";
    case ast::BinaryOperator::LogicalOr: return "||";
    case ast::BinaryOperator::Multiplication: return "*";
    case ast::BinaryOperator::NotEqual: return "!=";
    case ast::BinaryOperator::Remainder: return "%";
    case ast::BinaryOperator::ShiftLeft: return "<<";
    case ast::BinaryOperator::ShiftRight: return ">>";
    case ast::BinaryOperator::Subtraction: return "-";
    default: {
      throw std::domain_error("Unexpected value for `op`");
    }
  }
}

void EmitBinaryExpression(const ast::BinaryExpression &node, std::ostream &out) {
  out << "(";
  EmitExpression(*node.left, out);
  out << " ";
  out << serializeBinaryOperator(node.op);
  out << " ";
  EmitExpression(*node.right, out);
  out << ")";
}

void EmitCurrentAddress(const ast::CurrentAddress &, std::ostream &out) {
  out << ".";
}

void EmitIntegerLiteral(const ast::IntegerLiteral &node, std::ostream &out) {
  if (node.value > 0) {
    out << node.value;
  } else {
    out << "(" << node.value << ")";
  }
}

void EmitMnemonic(const ast::Mnemonic &node, std::ostream &out) {
  out << node.name;
}

void EmitOperand(const ast::Operand &node, std::ostream &out) {
  switch (node.node_type) {
    case ast::Node::Type::ImmediateOperand: {
      return EmitImmediateOperand(static_cast<const ast::ImmediateOperand &>(node), out);
    }
    case ast::Node::Type::RegisterOperand: {
      return EmitRegisterOperand(static_cast<const ast::RegisterOperand &>(node), out);
    }
    default: {
      throw std::domain_error("Unexpected value for `node.node_type`");
    }
  }
}

void EmitImmediateOperand(const ast::ImmediateOperand &node, std::ostream &out) {
  out << "$" << node.value;
}

void EmitRegisterOperand(const ast::RegisterOperand &node, std::ostream &out) {
  out << "%" << node.name;
}
}
}
