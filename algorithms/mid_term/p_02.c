#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
  int element;
  struct Node *parent;
  struct Node *left_child;
  struct Node *right_child;
} Node;

Node *createNode(int element) {
  Node *node = malloc(sizeof(*node));
  if (node == NULL) {
    exit(EXIT_FAILURE);
  }
  node->element = element;
  node->parent = NULL;
  node->left_child = NULL;
  node->right_child = NULL;
  return node;
}

bool isExternalNode(Node *node) {
  // 외부 노드 여부
  // 자식이 모두 없으면 외부 노드
  return node->left_child == NULL && node->right_child == NULL;
}

bool isInternalNode(Node *node) {
  return !isExternalNode(node);
}

bool isRoot(Node *node) {
  return node->parent == NULL;
}

void swapElements(Node *node, Node *parent_node) {
}

void advanceLast() {
}

void upHeap(Node *node) {
  if (isRoot(node)) {
    // root 이면 return
    return;
  }
  if (isExternalNode(node)) {
    // 외부 노드이면 종료
  }
  // 자식 노드의 element 가 더 크면 swapElement
  if (node->element > node->parent->element) {
    swapElements(node, node->parent);
  }
  // 부모에 대해서 upHeap 진행
  upHeap(node->parent);
}

void expandExternal(Node *node) {
}

void insertItem(int element) {
  advanceLast();

  // 새로운 노드 생성
  Node *new_node = createNode(element);
  expandExternal(new_node);
  upHeap(new_node);
}
