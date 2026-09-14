#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node;

typedef struct Tree {
  Node *root;
} Tree;

Node *createNode(int data) {
  // 노드 동적할당
  Node *node = malloc(sizeof(*node));
  if (node == NULL) {
    exit(EXIT_FAILURE);
  }

  // 자식은 NULL 초기화
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

Node *buildNode(void) {
  int x, y, z;

  // x y z 입력
  scanf("%d %d %d", &x, &y, &z);

  // x 노드 생성
  Node *node = createNode(x);

  // y != 0 이면 왼쪽 서브트리 생성
  if (y != 0) {
    node->left = buildNode();
  }

  // z != 0 이면 오른쪽 서브트리 생성
  if (z != 0) {
    node->right = buildNode();
  }

  // 현재 노드 반환
  return node;
}

void printNode(Node *root, char command_string[]) {
  printf(" %d", root->data);

  Node *current_node = root;

  // command_string 순회하여 명령 수행
  for (int i = 0; i < strlen(command_string); i++) {
    if (command_string[i] == 'L') {
      current_node = current_node->left;
    } else if (command_string[i] == 'R') {
      current_node = current_node->right;
    }
    printf(" %d", current_node->data);
  }
  printf("\n");
}

void destroyTree(Node *root) {
  if (root == NULL) {
    return;
  }

  // 재귀호출하여 메모리 해제
  destroyTree(root->left);
  destroyTree(root->right);
  free(root);
}

int main(void) {
  int node_count, search_count;
  char command_string[101];
  scanf("%d", &node_count);

  Tree tree;
  tree.root = buildNode();

  scanf("%d", &search_count);

  for (int i = 0; i < search_count; i++) {
    scanf("%s", command_string);
    printNode(tree.root, command_string);
  }
  destroyTree(tree.root);
}
