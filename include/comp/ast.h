#ifndef COMP_AST_H
#define COMP_AST_H

namespace comp {
  namespace ast {
    enum NodeType {
      Expression,
      Literal,
      Function
    };

    int create_node();
  }
}

#endif //COMP_AST_H
