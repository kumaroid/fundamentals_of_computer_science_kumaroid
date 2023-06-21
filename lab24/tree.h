#ifndef _TREE_H_
#define _TREE_H_

#include <stdlib.h>
#include "lexer.h"

typedefstructtree_node *Tree;
structtree_node {
    Token node;
    Tree left;
    Tree right;
};

Tree treeCreate(Token tokens[], intidx_left, intidx_right);
voidtreeDelete(Tree* t);
voidtreeInfix(Tree t);
voidtreePrint(Tree t, size_t depth);

#endif
