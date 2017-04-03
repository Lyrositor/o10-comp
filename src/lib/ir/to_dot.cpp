#include <iomanip>
#include <sstream>
#include <comp/ir/to_dot.h>

namespace comp {
namespace ir {
std::string pointer_to_string(void const *ptr) {
  std::stringstream id_stream;
  id_stream << std::setbase(16) << ptr;
  return id_stream.str();
}

void EmitVariableOperand(const VariableOperand &node, std::ostream &out) {
  out << "var" << pointer_to_string(node.variable.get());
}

void EmitConstantOperand(const ConstantOperand &node, std::ostream &out) {
  out << node.value;
}

void EmitOperand(const Operand &node, std::ostream &out) {
  switch (node.operand_type) {
    case Operand::Type::Variable: {
      EmitVariableOperand(static_cast<const VariableOperand &>(node), out);
      break;
    }
    case Operand::Type::Constant: {
      EmitConstantOperand(static_cast<const ConstantOperand &>(node), out);
      break;
    }
    default: {
      throw std::domain_error("Unexpected value for `node.operand_type` in `EmitOperand`");
    }
  }
}

std::string BinaryOperatorToString(const BinOp::BinaryOperator &node) {
  switch (node) {
    case BinOp::BinaryOperator::Addition: return "Addition";
    case BinOp::BinaryOperator::BitwiseAnd: return "BitwiseAnd";
    case BinOp::BinaryOperator::BitwiseOr: return "BitwiseOr";
    case BinOp::BinaryOperator::BitwiseXor: return "BitwiseXor";
    case BinOp::BinaryOperator::Division: return "Division";
    case BinOp::BinaryOperator::Equality: return "Equality";
    case BinOp::BinaryOperator::GreaterThan: return "GreaterThan";
    case BinOp::BinaryOperator::GreaterThanOrEqual: return "GreaterThanOrEqual";
    case BinOp::BinaryOperator::Inequality: return "Inequality";
    case BinOp::BinaryOperator::LeftShift: return "LeftShift";
    case BinOp::BinaryOperator::LessThan: return "LessThan";
    case BinOp::BinaryOperator::LessThanOrEqualTo: return "LessThanOrEqualTo";
    case BinOp::BinaryOperator::Multiplication: return "Multiplication";
    case BinOp::BinaryOperator::Remainder: return "Remainder";
    case BinOp::BinaryOperator::RightShift: return "RightShift";
    case BinOp::BinaryOperator::Subtraction: return "Subtraction";
    default: {
      throw std::domain_error("Unexpected value for `node` in `BinaryOperatorToString`");
    }
  }
}

void EmitBinOp(const BinOp &node, std::ostream &out) {
  EmitVariableOperand(*node.out, out);
  out << " := " << BinaryOperatorToString(node.binaryOperator) << "(";
  EmitOperand(*node.in1, out);
  out << ", ";
  EmitOperand(*node.in2, out);
  out << ");";
}

void EmitCopyOp(const CopyOp &node, std::ostream &out) {
  EmitVariableOperand(*node.out, out);
  out << " := Copy(";
  EmitOperand(*node.in, out);
  out << ");";
}

void EmitCallOp(const CallOp &node, std::ostream &out) {
  EmitVariableOperand(*node.out, out);
  out << " := CallOp(...);";
}

void EmitNoOp(const NoOp &node, std::ostream &out) {
  out << "NoOp;";
}

void EmitReturnOp(const ReturnOp &node, std::ostream &out) {
  out << "Return(";
  if (node.in != nullptr) {
    EmitOperand(*node.in, out);
  }
  out << ");";
}

void EmitTestOp(const TestOp &node, std::ostream &out) {
  out << "Test(";
  EmitOperand(*node.test, out);
  out << ");";
}

std::string UnaryOperatorToString(const UnaryOp::UnaryOperator &node) {
  switch (node) {
    case UnaryOp::UnaryOperator::BitwiseComplement: return "BitwiseComplement";
    case UnaryOp::UnaryOperator::LogicalNegation: return "LogicalNegation";
    case UnaryOp::UnaryOperator::UnaryMinus: return "UnaryMinus";
    default: {
      throw std::domain_error("Unexpected value for `node` in `UnaryOperatorToString`");
    }
  }
}

void EmitUnaryOp(const UnaryOp &node, std::ostream &out) {
  EmitVariableOperand(*node.out, out);
  out << " := " << UnaryOperatorToString(node.unaryOperator) << "(";
  EmitOperand(*node.in1, out);
  out << ");";
}

void EmitOp(const Op &node, std::ostream &out) {
  switch (node.op_type) {
    case Op::Type::BinOp: {
      EmitBinOp(static_cast<const BinOp &>(node), out);
      break;
    }
    case Op::Type::CopyOp: {
      EmitCopyOp(static_cast<const CopyOp &>(node), out);
      break;
    }
    case Op::Type::CallOp: {
      EmitCallOp(static_cast<const CallOp &>(node), out);
      break;
    }
    case Op::Type::NoOp: {
      EmitNoOp(static_cast<const NoOp &>(node), out);
      break;
    }
    case Op::Type::ReturnOp: {
      EmitReturnOp(static_cast<const ReturnOp &>(node), out);
      break;
    }
    case Op::Type::TestOp: {
      EmitTestOp(static_cast<const TestOp &>(node), out);
      break;
    }
    case Op::Type::UnaryOp: {
      EmitUnaryOp(static_cast<const UnaryOp &>(node), out);
      break;
    }
    default: {
      throw std::domain_error("Unexpected value for `node.op_type` in `EmitOp`");
    }
  }
}

void EmitBasicBlock(const BasicBlock &node, std::ostream &out) {
  std::vector<std::shared_ptr<Op>> ops = node.GetOps();
  if (ops.size() == 0) {
    out << ";";
  } else {
    for (size_t i = 0, l = ops.size(); i < l; i++) {
      if (i > 0) {
        out << "\n";
      }
      EmitOp(*ops[i], out);
    }
  }
}

std::string BasicBlockToString(const BasicBlock &node) {
  std::stringstream result;
  EmitBasicBlock(node, result);
  return result.str();
}

std::vector<std::shared_ptr<dot::ast::Statement>> BasicBlockToDot(const BasicBlock &node) {
  std::vector<std::shared_ptr<dot::ast::Assignment>> attributes;

  std::string ops = BasicBlockToString(node);
  attributes.push_back(dot::ast::Assignment::Create("label", ops));
  attributes.push_back(dot::ast::Assignment::Create("shape", "rectangle"));

  std::string id = "bb" + pointer_to_string(&node);
  std::vector<std::shared_ptr<dot::ast::Statement>> result;
  result.push_back(dot::ast::NodeStatement::Create(id, attributes));

  switch (node.GetType()) {
    case BasicBlock::Type::Incomplete: {
      break; // TODO: Dotted line ?
    }
    case BasicBlock::Type::Final: {
      break; // TODO: Double line width ?
    }
    case BasicBlock::Type::Jump: {
      result.push_back(dot::ast::EdgeStatement::Create({id, "bb" + pointer_to_string(node.GetBranch().get())}, {}));
      break;
    }
    case BasicBlock::Type::ConditionalJump: {
      std::shared_ptr<BasicBlock> branch_if_true = node.GetBranchIfTrue();
      std::shared_ptr<BasicBlock> branch_if_false = node.GetBranchIfFalse();
      std::vector<std::string> false_edge;
      result.push_back(
        dot::ast::EdgeStatement::Create(
          {id, "bb" + pointer_to_string(branch_if_true.get())},
          {dot::ast::Assignment::Create("color", "#45a03b")})
      );
      result.push_back(
        dot::ast::EdgeStatement::Create(
          {id, "bb" + pointer_to_string(branch_if_false.get())},
          {dot::ast::Assignment::Create("color", "#a52f29")})
      );
      break;
    }
    default: {
      throw std::domain_error("Unexpected value for `node.GetType()` in `BasicBlockToDot`");
    }
  }

  return result;
}

std::vector<std::shared_ptr<dot::ast::Statement>> ControlFlowGraphToDot(const ControlFlowGraph &node) {
  std::vector<std::shared_ptr<dot::ast::Statement>> result;
  std::set<std::shared_ptr<BasicBlock>> basic_blocks = node.GetBasicBlocks();
  for (auto basic_block : basic_blocks) {
    for (auto statement : BasicBlockToDot(*basic_block)) {
      result.push_back(statement);
    }
  }
  return result;
}

std::vector<std::shared_ptr<dot::ast::Statement>> FunctionSymbolToDot(const FunctionSymbol &node) {
  std::vector<std::shared_ptr<dot::ast::Statement>> body;

  std::vector<std::shared_ptr<dot::ast::Statement>> cfg = ControlFlowGraphToDot(*node.GetBody());
  for (auto statement : cfg) {
    body.push_back(statement);
  }

  std::string name = node.GetName();
  body.push_back(dot::ast::AssignmentStatement::Create("label", name + " @Function"));

  std::vector<std::shared_ptr<dot::ast::Statement>> result;
  std::string id = "cluster" + pointer_to_string(&node);
  result.push_back(dot::ast::SubgraphStatement::Create(std::shared_ptr<std::string>(new std::string(id)), body));
  return result;
}

std::unique_ptr<dot::ast::Graph> ProgramToDot(const Program &node) {
  std::vector<std::shared_ptr<dot::ast::Statement>> body;

  for (auto symbol: node.GetSymbols()) {
    std::vector<std::shared_ptr<dot::ast::Statement>> statements;
    switch (symbol->GetType()) {
      case ProgramSymbol::Type::Function: {
        statements = FunctionSymbolToDot(static_cast<const FunctionSymbol &>(*symbol));
        break;
      }
      case ProgramSymbol::Type::DataObject: {
        statements = {};
        break;
      }
    }
    for (auto statement : statements) {
      body.push_back(statement);
    }
  }

  return dot::ast::Graph::Create(true, true, nullptr, body);
}
}  // namespace ir
}  // namespace comp
