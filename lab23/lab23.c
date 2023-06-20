#include <stdio.h>
#include <stdlib.h>

typedef struct Tst {
    int key;
    struct Tst *son;
    struct Tst *brother;
} Node;

Node* create_tree(int val) {
    Node* tree = (Node*)malloc(sizeof(Node));
    if (tree == NULL) {
        exit(1);
    }
    tree->key = val;
    tree->son = NULL;
    tree->brother = NULL;
    return tree;
}

void delete_tree(Node *tree) {
    if (tree == NULL){
        return;
    }
    delete_tree(tree->son);
    delete_tree(tree->brother);
    free(tree);
}

Node* find_node(Node* root, int key) {
    if (root == NULL) {
        return NULL;
    }
    if (root->key == key) {
        return root;
    }
    Node* node = find_node(root->son, key);
    if (node != NULL) {
        return node;
    }
    return find_node(root->brother, key);
}

void tree_print(Node* root, int depth) {
    if (root == NULL) {
        return;
    }
    if (root->key != -1) { 
        printf("%*s", depth * 4, "");
        printf("%d\n", root->key);
    }
    tree_print(root->son, depth + 1);
    tree_print(root->brother, depth); 
}

Node* delete_subtree(Node* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return NULL;
    }

    char c;
    Node* curr = root;
    Node* prev = NULL;
    Node* new_root = NULL;

    while ((c = getchar()) != '\n') {
        if (c == ' ') {
            continue;
        }
        if (c == 'r') {
            prev = NULL;
            curr = root;
        } else if (c == 's') {
            if (curr->son == NULL) {
                printf("Node has no son\n");
                return root;
            }
            prev = curr;
            curr = curr->son;
        } else if (c == 'b') {
            if (prev == NULL || prev->brother == NULL) {
                printf("Node has no brother\n");
                return root;
            }
            curr = prev->brother;
            prev = NULL;
        }
    }
    if (curr == root) {
        new_root = root->brother ? root->brother : root->son;
        free(root);
        root = NULL;
        return new_root;
    }
    if (prev == NULL) {
        new_root = curr->brother ? curr->brother : curr->son;
        free(curr);
        curr = NULL;
        return root;
    }
    if (prev->son == curr) {
        prev->son = curr->brother;
    } else {
        Node* temp = prev->son;
        while (temp->brother != curr) {
            temp = temp->brother;
        }
        temp->brother = curr->brother;
    }
    curr->son = NULL;
    curr->brother = NULL;
    free(curr); 
    return root;
}


Node* add_node(Node* tree) {
    Node* t = tree;
    int value;
    char c;
    while ((c = getchar()) != 'r') {
        continue;
    }
    if (tree == NULL) {
        if (scanf("%d", &value) != 1) {
            printf("Input error\n");
            free(create_tree(value));
            return tree;
        }
        tree = create_tree(value);
        return tree;
    }
    while ((c = getchar()) != ' ') {
        if (c == 's') {
            t = t->son;
        }
        if (c == 'b') {
            t = t->brother;
        }
    }
    if (scanf("%d", &value) != 1) {
        printf("Input error\n");
        Node* ntree = create_tree(value);
        free(ntree);
        return tree;
    }
    Node* ntree = create_tree(value);
    if (t->son != NULL) {
        t = t->son;
        while (t->brother != NULL) {
            t = t->brother;
        }
        t->brother = ntree;
    } else {
        t->son = ntree;
    }
    return tree;
}

int is_width_monotonic(Node* root) {
    if (root == NULL) {
        return 1;
    }

    int prev_width = 0; 
    int curr_width = 0;
    int increasing = 0; 
    Node* level_start = root; 
    Node* curr_node = NULL; 
    Node* next_level_start = NULL;

    while (level_start != NULL) {
        curr_node = level_start;
        curr_width = 0;
        while (curr_node != NULL) {
            curr_width++;
            if (curr_node->son != NULL) {
                if (next_level_start == NULL) {
                    next_level_start = curr_node->son;
                } else {
                    Node* temp = next_level_start;
                    while (temp->brother != NULL) {
                        temp = temp->brother;
                    }
                    temp->brother = curr_node->son;
                }
            }
            curr_node = curr_node->brother;
        }
        if (prev_width > curr_width) {
            increasing = 0;
            break;
        } else if (prev_width < curr_width) {
            increasing = 1;
        }
        prev_width = curr_width;
        level_start = next_level_start;
        next_level_start = NULL;
    }
    return increasing;
}

int main() {
    char c;
    Node* root = NULL;
    while ((c = getchar()) != EOF) {
        if (c == 'a') {
            root = add_node(root);
        }
        if (c == 'd') {
            root = delete_subtree(root); 
        }
        if (c == 'p'){
            tree_print(root, 0);
        }
        if (c == 't'){
          if (is_width_monotonic(root)) {
            printf("The tree has monotonically increasing width at each level.\n");
          } else {
            printf("The tree does not have monotonically increasing width at each level.\n");
          }
        }
        if (c == 'q'){
            break;
        }
    }
  delete_tree(root);
    return 0;
}