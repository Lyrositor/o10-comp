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

void EmitOp(const Op &node, std::ostream &out) {
  switch (node.op_type) {
    case Op::Type::BinOp: {
      out << "BinOp;";
      break;
    }
    case Op::Type::Copy: {
      out << "Copy;";
      break;
    }
    case Op::Type::Call: {
      out << "Call;";
      break;
    }
    case Op::Type::NoOp: {
      out << "NoOp;";
      break;
    }
    case Op::Type::Return: {
      out << "Return;";
      break;
    }
    case Op::Type::UnaryOp: {
      out << "UnaryOp;";
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

  std::string id = "bb" + pointer_to_string(&node);
  std::vector<std::shared_ptr<dot::ast::Statement>> result;
  result.push_back(dot::ast::NodeStatement::Create(id, attributes));
  return result;
}

std::vector<std::shared_ptr<dot::ast::Statement>> ControlFlowGraphToDot(const ControlFlowGraph &node) {
  std::vector<std::shared_ptr<dot::ast::Statement>> result;
  for (auto statement : BasicBlockToDot(*node.GetSource())) {
    result.push_back(statement);
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
