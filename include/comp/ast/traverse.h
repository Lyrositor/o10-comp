#pragma once
#include "node.h"

#include <functional>

namespace comp {
namespace ast {
typedef std::function<void(const Node *node)> Visitor;

/**
 * Perform an in-order traversal of the sub-tree rooted at `ast`.
 *
 * @param ast Root of the subtree to traverse
 * @param visitor Vistor function, called for each node
 */
void traverse(const Node *ast, Visitor &visitor);
}
}
