#pragma once

#include <memory>

namespace comp {
namespace as {
namespace ast {
struct Node {
  enum class Type {
    AlignDirective,
    AscizDirective,
    CfiEndprocDirective,
    CfiStartprocDirective,
    CurrentAddress,
    EmptyStatement,
    GlobalDirective,
    GlobalSymbol,
    ImmediateOperand,
    Instruction,
    LocalSymbol,
    MemoryReference,
    Mnemonic,
    Program,
    QuadDirective,
    RegisterOperand,
    SizeDirective,
    TextDirective,
    TypeDirective
  };

  Node(Type node_type);
  virtual ~Node() = 0;

  const Type node_type;
};
}  // namespace ast
}  // namespace as
}  // namespace comp
