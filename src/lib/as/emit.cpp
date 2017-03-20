#include <comp/as/emit.h>
#include <comp/ast.h>
#include <comp/as/ast.h>

namespace comp {
namespace as {
void emitProgram(const ast::Program &node, std::ostream &out) {
  for (auto statement : node.body) {
    emitStatement(*statement, out);
  }
}

void emitStatement(const ast::Statement &node, std::ostream &out) {
  switch (node.node_type) {
    case ast::Node::Type::AlignDirective: {
      return emitAlignDirective(static_cast<const ast::AlignDirective &>(node), out);
    }
    case ast::Node::Type::CfiEndprocDirective: {
      return emitCfiEndprocDirective(static_cast<const ast::CfiEndprocDirective &>(node), out);
    }
    case ast::Node::Type::CfiStartprocDirective: {
      return emitCfiStartprocDirective(static_cast<const ast::CfiStartprocDirective &>(node), out);
    }
    case ast::Node::Type::EmptyStatement: {
      return emitEmptyStatement(static_cast<const ast::EmptyStatement &>(node), out);
    }
    case ast::Node::Type::GlobalDirective: {
      return emitGlobalDirective(static_cast<const ast::GlobalDirective &>(node), out);
    }
    case ast::Node::Type::Instruction: {
      return emitInstruction(static_cast<const ast::Instruction &>(node), out);
    }
    case ast::Node::Type::SizeDirective: {
      return emitSizeDirective(static_cast<const ast::SizeDirective &>(node), out);
    }
    case ast::Node::Type::TextDirective: {
      return emitTextDirective(static_cast<const ast::TextDirective &>(node), out);
    }
    case ast::Node::Type::TypeDirective: {
      return emitTypeDirective(static_cast<const ast::TypeDirective &>(node), out);
    }
    default: {
      throw std::domain_error("Unexpected value for `node.node_type`");
    }
  }
}

void emitLabels(
  const std::vector<std::shared_ptr<ast::Symbol>> &labels,
  std::ostream &out,
  bool add_trailing_space) {
  for (size_t i = 0, l = labels.size(); i < l; i++) {
    emitSymbol(*labels[i], out);
    out << (i < l - 1 || add_trailing_space ? ": " : ":");
  }
}

void emitAlignDirective(const ast::AlignDirective &node, std::ostream &out) {
  emitLabels(node.labels, out, true);
  out << ".align ";
  emitExpression(*node.alignment_value, out);
  if (node.fill_value != nullptr || node.max_skipped_bytes != nullptr) {
    out << ", ";
  }
  if (node.fill_value != nullptr) {
    emitExpression(*node.fill_value, out);
  }
  if (node.max_skipped_bytes != nullptr) {
    out << ", ";
    emitExpression(*node.max_skipped_bytes, out);
  }
  out << "\n";
}

void emitCfiEndprocDirective(const ast::CfiEndprocDirective &node, std::ostream &out) {
  emitLabels(node.labels, out, true);
  out << ".cfi_endproc\n";
}

void emitCfiStartprocDirective(const ast::CfiStartprocDirective &node, std::ostream &out) {
  emitLabels(node.labels, out, true);
  out << ".cfi_startproc\n";
}

void emitEmptyStatement(const ast::EmptyStatement &node, std::ostream &out) {
  emitLabels(node.labels, out, false);
  out << "\n";
}

void emitGlobalDirective(const ast::GlobalDirective &node, std::ostream &out) {
  emitLabels(node.labels, out, true);
  out << ".global ";
  emitSymbol(*node.symbol, out);
  out << "\n";
}

void emitInstruction(const ast::Instruction &node, std::ostream &out) {
  emitLabels(node.labels, out, true);
  emitMnemonic(*node.mnemonic, out);
  for (size_t i = 0, l = node.operands.size(); i < l; i++) {
    out << (i == 0 ? " " : ", ");
    emitOperand(*node.operands[i], out);
  }
  out << "\n";
}

void emitSizeDirective(const ast::SizeDirective &node, std::ostream &out) {
  emitLabels(node.labels, out, true);
  out << ".size ";
  emitSymbol(*node.symbol, out);
  out << ", ";
  emitExpression(*node.size, out);
  out << "\n";
}

void emitTextDirective(const ast::TextDirective &node, std::ostream &out) {
  emitLabels(node.labels, out, true);
  out << ".text\n";
}

void emitTypeDirective(const ast::TypeDirective &node, std::ostream &out) {
  emitLabels(node.labels, out, true);
  out << ".type ";
  emitSymbol(*node.symbol, out);
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

void emitExpression(const ast::Expression &node, std::ostream &out) {
  switch (node.node_type) {
    case ast::Node::Type::BigIntegerLiteral: {
      return emitBigIntegerLiteral(static_cast<const ast::BigIntegerLiteral &>(node), out);
    }
    case ast::Node::Type::BinaryExpression: {
      return emitBinaryExpression(static_cast<const ast::BinaryExpression &>(node), out);
    }
    case ast::Node::Type::CurrentAddress: {
      return emitCurrentAddress(static_cast<const ast::CurrentAddress &>(node), out);
    }
    case ast::Node::Type::GlobalSymbol: {
      return emitGlobalSymbol(static_cast<const ast::GlobalSymbol &>(node), out);
    }
    case ast::Node::Type::IntegerLiteral: {
      return emitIntegerLiteral(static_cast<const ast::IntegerLiteral &>(node), out);
    }
    case ast::Node::Type::LocalSymbol: {
      return emitLocalSymbol(static_cast<const ast::LocalSymbol &>(node), out);
    }
    default: {
      throw std::domain_error("Unexpected value for `node.node_type`");
    }
  }
}

void emitSymbol(const ast::Symbol &node, std::ostream &out) {
  switch (node.node_type) {
    case ast::Node::Type::GlobalSymbol: {
      return emitGlobalSymbol(static_cast<const ast::GlobalSymbol &>(node), out);
    }
    case ast::Node::Type::LocalSymbol: {
      return emitLocalSymbol(static_cast<const ast::LocalSymbol &>(node), out);
    }
    default: {
      throw std::domain_error("Unexpected value for `node.node_type`");
    }
  }
}

void emitGlobalSymbol(const ast::GlobalSymbol &node, std::ostream &out) {
  out << node.name;
}

void emitLocalSymbol(const ast::LocalSymbol &node, std::ostream &out) {
  out << ".L" << node.name;
}

void emitBigIntegerLiteral(const ast::BigIntegerLiteral &node, std::ostream &out) {
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

void emitBinaryExpression(const ast::BinaryExpression &node, std::ostream &out) {
  out << "(";
  emitExpression(*node.left, out);
  out << " ";
  out << serializeBinaryOperator(node.op);
  out << " ";
  emitExpression(*node.right, out);
  out << ")";
}

void emitCurrentAddress(const ast::CurrentAddress &, std::ostream &out) {
  out << ".";
}

void emitIntegerLiteral(const ast::IntegerLiteral &node, std::ostream &out) {
  if (node.value > 0) {
    out << node.value;
  } else {
    out << "(" << node.value << ")";
  }
}

void emitMnemonic(const ast::Mnemonic &node, std::ostream &out) {
  out << node.name;
}

void emitOperand(const ast::Operand &node, std::ostream &out) {
  switch (node.node_type) {
    case ast::Node::Type::ImmediateOperand: {
      return emitImmediateOperand(static_cast<const ast::ImmediateOperand &>(node), out);
    }
    case ast::Node::Type::RegisterOperand: {
      return emitRegisterOperand(static_cast<const ast::RegisterOperand &>(node), out);
    }
    default: {
      throw std::domain_error("Unexpected value for `node.node_type`");
    }
  }
}

void emitImmediateOperand(const ast::ImmediateOperand &node, std::ostream &out) {
  out << "$" << node.value;
}

void emitRegisterOperand(const ast::RegisterOperand &node, std::ostream &out) {
  out << "%" << node.name;
}
}
}
