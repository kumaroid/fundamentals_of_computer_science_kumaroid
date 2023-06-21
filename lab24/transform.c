#include "tree.h"
#include "transform.h"
#include <math.h>

voidswapNode(Tree** a, Tree** b) {
    Tree* tmp = *a;
    *a = *b;
    *b = tmp;
}

int transform(Tree* t) {
staticint count = 0;
if (*t == NULL) {
return count;
    }
if ((*t)->node.type == INTEGER) {
        ++count;
    }
}

inttreeTransform(Tree* t) {
staticint count = 0;
if ((*t) == NULL) {
return count;
    }
treeTransform(&((*t)->left));
treeTransform(&((*t)->right));

count = transform(t);
}
