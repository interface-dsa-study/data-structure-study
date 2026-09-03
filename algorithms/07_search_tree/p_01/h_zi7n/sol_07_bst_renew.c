#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right, *parent;
}Node;

Node* root = NULL;

Node *getNode() {
    Node* new_node = malloc(sizeof(Node*));
    new_node->left->key = 0;
    new_node->right->key = 0;
    return new_node;
}

Node* treeSearch(int key) {
    
}