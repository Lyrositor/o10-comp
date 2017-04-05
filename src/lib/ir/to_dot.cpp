#include <iomanip>
#include <sstream>

#include <comp/ir/to_dot.h>
#include <comp/utils.h>
#include <map>
#include <vector>
#include <sstream>

namespace comp {
namespace ir {
size_t IdentifiersTable::GetFunctionIdentifier(const FunctionSymbol &f){
  const void* fvoid = static_cast<const void*>(&f);
  if(identifers_map.find(fvoid)==identifers_map.end()) {
    identifers_map[fvoid] = counter++;
  }
  return identifers_map[static_cast<const void*>(fvoid)];
}

size_t IdentifiersTable::GetVariableIdentifier(const Variable &v){
  const void* vvoid = static_cast<const void*>(&v);
  if(identifers_map.find(vvoid)==identifers_map.end()) {
    identifers_map[vvoid] = counter++;
  }
  return identifers_map[vvoid];
}

size_t IdentifiersTable::GetBasicBlockIdentifier(const BasicBlock &bb){
  const void* bbvoid = static_cast<const void*>(&bb);
  if(identifers_map.find(bbvoid)==identifers_map.end()) {
    identifers_map[bbvoid] = counter++;
  }
  return identifers_map[bbvoid];
}


void EmitVariableOperand(const VariableOperand &node, std::ostream &out, IdentifiersTable &it) {
  out << "var" << it.GetVariableIdentifier(*node.variable.get());
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

void EmitBinOp(const BinOp &node, std::ostream &out, IdentifiersTable &it) {
  EmitVariableOperand(*node.out, out, it);
  out << " := " << BinaryOperatorToString(node.binaryOperator) << "(";
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
  EmitVariableOperand(*node.out, out, it);
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
    case UnaryOp::UnaryOperator::BitwiseComplement: return "BitwiseComplement";
    case UnaryOp::UnaryOperator::LogicalNegation: return "LogicalNegation";
    case UnaryOp::UnaryOperator::UnaryMinus: return "UnaryMinus";
    default: {
      throw std::domain_error("Unexpected value for `node` in `UnaryOperatorToString`");
    }
  }
}

void EmitUnaryOp(const UnaryOp &node, std::ostream &out, IdentifiersTable &it) {
  EmitVariableOperand(*node.out, out, it);
  out << " := " << UnaryOperatorToString(node.unaryOperator) << "(";
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
    default: {
      throw std::domain_error("Unexpected value for `node.op_type` in `EmitOp`");
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

std::vector<std::shared_ptr<dot::ast::Statement>> BasicBlockToDot(const BasicBlock &node,IdentifiersTable &it) {
  std::vector<std::shared_ptr<dot::ast::Assignment>> attributes;

  std::string ops = BasicBlockToString(node,it);
  attributes.push_back(dot::ast::Assignment::Create("label", ops));
  attributes.push_back(dot::ast::Assignment::Create("shape", "rectangle"));

  std::stringstream ss;
  ss << "bb" << it.GetBasicBlockIdentifier(node);
  std::string id = ss.str() ;
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
      std::stringstream ss;
      ss << "bb" << it.GetBasicBlockIdentifier(*node.GetBranch().get());
      std::string stringss = ss.str() ;
      result.push_back(dot::ast::EdgeStatement::Create({id, stringss }, {}));
      break;
    }
    case BasicBlock::Type::ConditionalJump: {
      result.push_back(dot::ast::NodeStatement::Create(id, attributes));
      std::shared_ptr<BasicBlock> branch_if_true = node.GetBranchIfTrue();
      std::shared_ptr<BasicBlock> branch_if_false = node.GetBranchIfFalse();
      std::vector<std::string> false_edge;
      std::stringstream ss;
      ss << "bb" << it.GetBasicBlockIdentifier(*branch_if_true.get());
      std::string stringss = ss.str() ;
      result.push_back(
        dot::ast::EdgeStatement::Create(
          {id, stringss},
          {dot::ast::Assignment::Create("color", "#45a03b")})
      );
      std::stringstream ss2;
      ss2 << "bb" << it.GetBasicBlockIdentifier(*branch_if_false.get());
      std::string stringss2 = ss2.str() ;
      result.push_back(
        dot::ast::EdgeStatement::Create(
          {id, stringss2},
          {dot::ast::Assignment::Create("color", "#a52f29")})
      );
      break;
    }
    case BasicBlock::Type::Return: {
      attributes.push_back(dot::ast::Assignment::Create("style", "bold"));
      result.push_back(dot::ast::NodeStatement::Create(id, attributes));
      break;
    }
    default: {
      throw std::domain_error("Unexpected value for `node.GetType()` in `BasicBlockToDot`");
    }
  }

  return result;
}

std::vector<std::shared_ptr<dot::ast::Statement>> ControlFlowGraphToDot(const ControlFlowGraph &node,IdentifiersTable &it) {
  std::vector<std::shared_ptr<dot::ast::Statement>> result;
  std::set<std::shared_ptr<BasicBlock>> basic_blocks = node.GetBasicBlocks();
  for (auto basic_block : basic_blocks) {
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
  std::stringstream ss;
  ss << "cluster" << it.GetFunctionIdentifier(node);
  std::string id = ss.str() ;
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
