#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int key;
  struct Node *parent;
  struct Node *left_child;
  struct Node *right_child;
} Node;

typedef struct Tree {
  Node *root_node;
} Tree;

Node *createExternalNode(Node *parent) {
  Node *new_node = malloc(sizeof(*new_node));
  if (new_node == NULL) {
    exit(EXIT_FAILURE);
  }
  new_node->key = 0;
  new_node->parent = parent;
  new_node->left_child = NULL;
  new_node->right_child = NULL;
  return new_node;
}

/**
 * 새로운 Tree 생성
 * 빈 Tree는 외부 노드 한개로 구성되어있음
 */
Tree *createTree(void) {
  Tree *new_tree = malloc(sizeof(*new_tree));
  if (new_tree == NULL) {
    exit(EXIT_FAILURE);
  }
  Node *root_node = createExternalNode(NULL);
  new_tree->root_node = root_node;
  return new_tree;
}

bool isExternalNode(Node *node) {
  return node->left_child == NULL && node->right_child == NULL;
}

bool isInternalNode(Node *node) {
  return !isExternalNode(node);
}

void convertExternalNodeToInternalNode(Node *external_node, int key) {
  // 내부 노드인경우 return
  if (isInternalNode(external_node)) {
    return;
  }
  external_node->key = key;
  external_node->left_child = createExternalNode(external_node);
  external_node->right_child = createExternalNode(external_node);
}

Node *inOrderSucc(Node *node) {
  if (node == NULL || isInternalNode(node)) {
    return NULL;
  }

  Node *successor_node = node->right_child;
  while (isInternalNode(successor_node)) {
    successor_node = successor_node->left_child;
  }
  return successor_node;
}

Node *findSiblingNode(Node *node) {
  if (node->parent == NULL) {
    return NULL;
  }
  Node *parent_node = node->parent;
  if (parent_node->left_child == node) {
    return parent_node->right_child;
  }
  return parent_node->left_child;
}

Node *treeSearch(Node *node, int key) {
  // 외부 노드에 도달한 경우 해당 외부 노드가 key가 있어야 할 자리
  if (isExternalNode(node)) {
    return node;
  }

  if (key == node->key) {
    // 찾은 경우 해당 내부 노드 반환
    return node;
  }
  if (key > node->key) {
    // key 가 더 큰 경우 오른쪽 이진 탐색 진행
    return treeSearch(node->right_child, key);
  }
  // key 가 더 작은 경우 왼쪽 이진 탐색 진행
  return treeSearch(node->left_child, key);
}

void insertItem(Tree *tree, int key) {
  if (tree == NULL) {
    return;
  }
  // 해당 key 가 들어갈 위치 탐색
  Node *target_node = treeSearch(tree->root_node, key);

  // 이미 해당 key가 내부 노드로 존재하는 경우
  if (isInternalNode(target_node)) {
    return;
  }

  // 해당 key가 들어갈 외부 노드를 내부 노드로 변경
  convertExternalNodeToInternalNode(target_node, key);
}

int getChildCount(Node *node) {
  if (isExternalNode(node->left_child) && isExternalNode(node->right_child)) {
    return 0;
  }
  if (isInternalNode(node->left_child) && isInternalNode(node->right_child)) {
    return 2;
  }
  return 1;
}

bool isRootNode(Tree *tree, Node *node) {
  return tree->root_node == node;
}

void reduceExternal(Tree *tree, Node *node) {
  int child_count = getChildCount(node);

  if (child_count == 0 || child_count == 1) {
    // 자식이 0개 또는 1개

    if (isRootNode(tree, node)) {
      // 삭제 대상이 루트 노드인 경우
    }
    // 삭제 대상이 루트 노드가 아닌 경우
  }
  // 자식이 2개
}

int removeElement(Tree *tree, int key) {
  // 삭제할 노드 확인
  Node *target_node = treeSearch(tree->root_node, key);

  // 삭제할 노드가 NULL 이거나 외부 노드인 경우 0 반환
  if (target_node == NULL || isExternalNode(target_node)) {
    return 0;
  }
  int result_key = target_node->key;
  reduceExternal(tree, target_node);
  return result_key;
}

void printPreorderTraversal(Node *node) {
  if (node == NULL || isExternalNode(node)) {
    return;
  }
  printf(" %d", node->key);
  printPreorderTraversal(node->left_child);
  printPreorderTraversal(node->right_child);
  printf("\n");
}

void destroyNode(Node *node) {
  if (node == NULL) {
    return;
  }
  destroyNode(node->left_child);
  destroyNode(node->right_child);
  free(node);
}

void destroyTree(Tree *tree) {
  if (tree == NULL) {
    return;
  }
  destroyNode(tree->root_node);
  free(tree);
}

int main(void) {
  char command;
  int key;

  Tree *tree = createTree();

  while (true) {
    scanf(" %c", &command);
    if (command == 'i') {
      scanf(" %d", &key);
      insertItem(tree, key);
    } else if (command == 'd') {
      scanf(" %d", &key);
      removeElement(tree, key);
    } else if (command == 's') {
      scanf(" %d", &key);
      Node *target_node = treeSearch(tree->root_node, key);
      if (isExternalNode(target_node)) {
        printf("X\n");
      }
      printf("%d\n", target_node->key);
    } else if (command == 'p') {
      printPreorderTraversal(tree->root_node);
    } else if (command == 'q') {
      break;
    }
  }
  destroyTree(tree);
  return EXIT_SUCCESS;
}
