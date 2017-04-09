#include <iomanip>
#include <sstream>
#include <vector>

#include <comp/ir/to_dot.h>
#include <comp/utils.h>

namespace comp {
namespace ir {
IdentifiersTable::IdentifiersTable() :
  basic_blocks_counter(0), basic_blocks_map(),
  variables_counter(0),  variables_map(),
  functions_counter(0), functions_map() {
}

IdentifiersTable::~IdentifiersTable() {
}

std::string IdentifiersTable::GetFunctionId(const FunctionSymbol &function_symbol){
  if(functions_map.find(&function_symbol) == functions_map.end()) {
    functions_map[&function_symbol] = functions_counter++;
  }
  return std::string("cluster") + std::to_string(functions_map[&function_symbol]);
}

std::string IdentifiersTable::GetVariableId(const Variable &variable){
  if(variables_map.find(&variable) == variables_map.end()) {
    variables_map[&variable] = variables_counter++;
  }
  return std::string("var") + std::to_string(variables_map[&variable]);
}

std::string IdentifiersTable::GetBasicBlockId(const BasicBlock &basic_block){
  if(basic_blocks_map.find(&basic_block) == basic_blocks_map.end()) {
    basic_blocks_map[&basic_block] = basic_blocks_counter++;
  }
  return std::string("bb") + std::to_string(basic_blocks_map[&basic_block]);
}

void EmitVariableOperand(const VariableOperand &node, std::ostream &out, IdentifiersTable &it) {
  out << it.GetVariableId(*node.variable);
}

void EmitIndirectOperand(const IndirectOperand &node, std::ostream &out, IdentifiersTable &it) {
  out << "*(";
  EmitOperand(*node.address, out, it);
  out << ")";
}

void EmitConstantOperand(const ConstantOperand &node, std::ostream &out) {
  out << node.value;
}

void EmitOperand(const Operand &node, std::ostream &out, IdentifiersTable &it) {
  switch (node.operand_type) {
    case Operand::Type::Variable: {
      EmitVariableOperand(static_cast<const VariableOperand &>(node), out, it);
      break;
    }
    case Operand::Type::Indirect: {
      EmitIndirectOperand(static_cast<const IndirectOperand &>(node), out, it);
      break;
    }
    case Operand::Type::Constant: {
      EmitConstantOperand(static_cast<const ConstantOperand &>(node), out);
      break;
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
  }
  throw Exception("unexpected ir binary operator");
}

void EmitBinOp(const BinOp &node, std::ostream &out, IdentifiersTable &it) {
  EmitOperand(*node.out, out, it);
  out << " := " << BinaryOperatorToString(node.binary_operator) << "(";
  EmitOperand(*node.in1, out, it);
  out << ", ";
  EmitOperand(*node.in2, out, it);
  out << ");";
}

void EmitCastOp(const CastOp &node, std::ostream &out, IdentifiersTable &it) {
  EmitVariableOperand(*node.out, out, it);
  out << " := Cast(";
  EmitOperand(*node.in, out, it);
  out << ");";
}

void EmitCopyOp(const CopyOp &node, std::ostream &out, IdentifiersTable &it) {
  EmitOperand(*node.out, out, it);
  out << " := Copy(";
  EmitOperand(*node.in, out, it);
  out << ");";
}

void EmitCallOp(const CallOp &node, std::ostream &out, IdentifiersTable &it) {
  EmitVariableOperand(*node.out, out, it);
  out << " := CallOp(...);";
}

void EmitNoOp(const NoOp &node, std::ostream &out, IdentifiersTable &it) {
  UNUSED(node);
  UNUSED(it);
  out << "NoOp;";
}

void EmitReturnOp(const ReturnOp &node, std::ostream &out, IdentifiersTable &it) {
  out << "Return(";
  if (node.in != nullptr) {
    EmitOperand(*node.in, out, it);
  }
  out << ");";
}

void EmitTestOp(const TestOp &node, std::ostream &out, IdentifiersTable &it) {
  out << "Test(";
  EmitOperand(*node.test, out, it);
  out << ");";
}

std::string UnaryOperatorToString(const UnaryOp::UnaryOperator &node) {
  switch (node) {
    case UnaryOp::UnaryOperator::AddressOf: return "AddressOf";
    case UnaryOp::UnaryOperator::BitwiseComplement: return "BitwiseComplement";
    case UnaryOp::UnaryOperator::LogicalNegation: return "LogicalNegation";
    case UnaryOp::UnaryOperator::UnaryMinus: return "UnaryMinus";
    case UnaryOp::UnaryOperator::Decrement: return "PrefixDecrement";
    case UnaryOp::UnaryOperator::Increment: return "PrefixIncrement";
  }
  throw Exception("unexpected ir unary operator type");
}

void EmitUnaryOp(const UnaryOp &node, std::ostream &out, IdentifiersTable &it) {
  EmitOperand(*node.out, out, it);
  out << " := " << UnaryOperatorToString(node.unary_operator) << "(";
  EmitOperand(*node.in1, out,it);
  out << ");";
}

void EmitOp(const Op &node, std::ostream &out, IdentifiersTable &it) {
  switch (node.op_type) {
    case Op::Type::BinOp: {
      EmitBinOp(static_cast<const BinOp &>(node), out, it);
      break;
    }
    case Op::Type::CastOp: {
      EmitCastOp(static_cast<const CastOp &>(node), out, it);
      break;
    }
    case Op::Type::CopyOp: {
      EmitCopyOp(static_cast<const CopyOp &>(node), out, it);
      break;
    }
    case Op::Type::CallOp: {
      EmitCallOp(static_cast<const CallOp &>(node), out, it);
      break;
    }
    case Op::Type::NoOp: {
      EmitNoOp(static_cast<const NoOp &>(node), out, it);
      break;
    }
    case Op::Type::ReturnOp: {
      EmitReturnOp(static_cast<const ReturnOp &>(node), out, it);
      break;
    }
    case Op::Type::TestOp: {
      EmitTestOp(static_cast<const TestOp &>(node), out, it);
      break;
    }
    case Op::Type::UnaryOp: {
      EmitUnaryOp(static_cast<const UnaryOp &>(node), out, it);
      break;
    }
  }
}

void EmitBasicBlock(const BasicBlock &node, std::ostream &out,IdentifiersTable &it) {
  std::vector<std::shared_ptr<Op>> ops = node.GetOps();
  if (ops.size() == 0) {
    out << ";";
  } else {
    for (size_t i = 0, l = ops.size(); i < l; i++) {
      if (i > 0) {
        out << "\n";
      }
      EmitOp(*ops[i], out, it);
    }
  }
}

std::string BasicBlockToString(const BasicBlock &node,IdentifiersTable &it) {
  std::stringstream result;
  EmitBasicBlock(node, result,it);
  return result.str();
}

std::vector<std::shared_ptr<dot::ast::Statement>> BasicBlockToDot(const BasicBlock &node, IdentifiersTable &it) {
  std::vector<std::shared_ptr<dot::ast::Assignment>> attributes;

  std::string ops = BasicBlockToString(node,it);
  attributes.push_back(dot::ast::Assignment::Create("label", ops));
  attributes.push_back(dot::ast::Assignment::Create("shape", "rectangle"));

  std::string id = it.GetBasicBlockId(node);
  std::vector<std::shared_ptr<dot::ast::Statement>> result;

  switch (node.GetType()) {
    case BasicBlock::Type::Incomplete: {
      attributes.push_back(dot::ast::Assignment::Create("style", "dotted"));
      result.push_back(dot::ast::NodeStatement::Create(id, attributes));
      break;
    }
    case BasicBlock::Type::Final: {
      attributes.push_back(dot::ast::Assignment::Create("style", "bold"));
      result.push_back(dot::ast::NodeStatement::Create(id, attributes));
      break;
    }
    case BasicBlock::Type::Jump: {
      result.push_back(dot::ast::NodeStatement::Create(id, attributes));
      result.push_back(dot::ast::EdgeStatement::Create({id, it.GetBasicBlockId(*node.GetBranch())}, {}));
      break;
    }
    case BasicBlock::Type::ConditionalJump: {
      result.push_back(dot::ast::NodeStatement::Create(id, attributes));
      std::shared_ptr<BasicBlock> branch_if_true = node.GetBranchIfTrue();
      std::shared_ptr<BasicBlock> branch_if_false = node.GetBranchIfFalse();
      std::vector<std::string> false_edge;
      result.push_back(
        dot::ast::EdgeStatement::Create(
          {id, it.GetBasicBlockId(*branch_if_true)},
          {dot::ast::Assignment::Create("color", "#45a03b")})
      );
      result.push_back(
        dot::ast::EdgeStatement::Create(
          {id, it.GetBasicBlockId(*branch_if_false)},
          {dot::ast::Assignment::Create("color", "#a52f29")})
      );
      break;
    }
    case BasicBlock::Type::Return: {
      attributes.push_back(dot::ast::Assignment::Create("style", "bold"));
      result.push_back(dot::ast::NodeStatement::Create(id, attributes));
      break;
    }
  }

  return result;
}

std::vector<std::shared_ptr<dot::ast::Statement>> ControlFlowGraphToDot(const ControlFlowGraph &node, IdentifiersTable &it) {
  std::vector<std::shared_ptr<dot::ast::Statement>> result;
  for (auto basic_block : node.GetBasicBlocks()) {
    for (auto statement : BasicBlockToDot(*basic_block,it)) {
      result.push_back(statement);
    }
  }
  return result;
}

std::vector<std::shared_ptr<dot::ast::Statement>> FunctionSymbolToDot(const FunctionSymbol &node, IdentifiersTable &it) {
  std::vector<std::shared_ptr<dot::ast::Statement>> body;

  std::vector<std::shared_ptr<dot::ast::Statement>> cfg = ControlFlowGraphToDot(*node.GetBody(),it);
  for (auto statement : cfg) {
    body.push_back(statement);
  }

  std::string name = node.GetName();
  body.push_back(dot::ast::AssignmentStatement::Create("label", name + " @Function"));

  std::vector<std::shared_ptr<dot::ast::Statement>> result;
  std::string id = it.GetFunctionId(node);
  result.push_back(dot::ast::SubgraphStatement::Create(std::shared_ptr<std::string>(new std::string(id)), body));
  return result;
}

std::unique_ptr<dot::ast::Graph> ProgramToDot(const Program &node) {
  std::vector<std::shared_ptr<dot::ast::Statement>> body;
  IdentifiersTable identifiersTable;

  for (auto symbol: node.GetSymbols()) {
    std::vector<std::shared_ptr<dot::ast::Statement>> statements;
    switch (symbol->GetType()) {
      case ProgramSymbol::Type::Function: {
        statements = FunctionSymbolToDot(static_cast<const FunctionSymbol &>(*symbol),identifiersTable);
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
