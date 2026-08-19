#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int key;
  struct Node *parent;
  struct Node *left_child;
  struct Node *right_child;
} Node;

typedef struct BinarySearchTree {
  Node *root;
} BinarySearchTree;

Node *createExternalNode(Node *parent) {
  Node *node = malloc(sizeof(*node));
  if (node == NULL) {
    exit(EXIT_FAILURE);
  }
  node->key = 0;
  node->parent = parent;
  node->left_child = NULL;
  node->right_child = NULL;
  return node;
}

BinarySearchTree *createBinarySearchTree(void) {
  BinarySearchTree *tree = malloc(sizeof(*tree));
  if (tree == NULL) {
    exit(EXIT_FAILURE);
  }
  tree->root = createExternalNode(NULL);
  return tree;
}

bool isExternalNode(Node *node) {
  return node->left_child == NULL && node->right_child == NULL;
}

bool isInternalNode(Node *node) {
  return !isExternalNode(node);
}

Node *treeSearch(Node *node, int key) {
  if (isExternalNode(node)) {
    return node;
  }

  if (node->key == key) {
    return node;
  }

  if (key < node->key) {
    return treeSearch(node->left_child, key);
  }

  return treeSearch(node->right_child, key);
}

Node *findNodeByPreorderTraversal(Node *node, int key) {
  if (node == NULL) {
    return NULL;
  }

  if (node->key == key) {
    return node;
  }

  findNodeByPreorderTraversal(node->left_child, key);
  findNodeByPreorderTraversal(node->right_child, key);
  return NULL;
}

int findElement(Node *node, int key) {
  Node *target_node = treeSearch(node, key);
  if (target_node == NULL) {
    return 0;
  }
  return target_node->key;
}

Node *findInorderSuccessor(Node *node) {
  Node *successorNode = node->right_child;

  while (isInternalNode(successorNode->left_child)) {
    successorNode = successorNode->left_child;
  }

  return successorNode;
}

Node *findSiblingNode(Node *node) {
  Node *parent_node = node->parent;

  if (parent_node->left_child == node) {
    return parent_node->right_child;
  }
  return parent_node->left_child;
}

Node *reduceExternal(BinarySearchTree *tree, Node *externalNode) {
}

int removeElement(BinarySearchTree *tree, int key) {
}

void insertItem(Node *node, int key) {
  if (node == NULL) {
    return;
  }
  Node *target_node = treeSearch(node, key);
  target_node->key = key;
  target_node->left_child = createExternalNode(target_node);
  target_node->right_child = createExternalNode(target_node);
}

void printPreorderTraversal(Node *node) {
  if (node == NULL) {
    printf("\n");
    return;
  }
  printf(" %d", node->key);
  printPreorderTraversal(node->left_child);
  printPreorderTraversal(node->right_child);
}

void destroyNode(Node *node) {
  if (node == NULL) {
    return;
  }
  destroyNode(node->left_child);
  destroyNode(node->right_child);
  free(node);
}

int main(void) {
  char operator;
  int key;
  BinarySearchTree *tree = createBinarySearchTree();

  while (true) {
    scanf("%c", &operator);

    if (operator == 'i') {
      scanf(" %d", &key);
      insertItem(tree->root, key);
    } else if (operator == 'd') {
      scanf(" %d", &key);
    } else if (operator == 's') {
      scanf(" %d", &key);
      int found_key = findElement(tree->root, key);
      if (found_key == 0) {
        printf("X\n");
      }
      printf("%d\n", found_key);
    } else if (operator == 'p') {
      printPreorderTraversal(tree->root);
    } else if (operator == 'q') {
      break;
    }
  }

  destroyNode(tree->root);
  free(tree);
  return EXIT_SUCCESS;
}
