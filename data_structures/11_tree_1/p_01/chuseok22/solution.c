#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node;

Node *createNode(int data, Node *left, Node *right) {
  Node *node = malloc(sizeof(*node));

  if (node == NULL) {
    exit(EXIT_FAILURE);
  }

  node->data = data;
  node->left = left;
  node->right = right;

  return node;
}

void printNodeAndChildren(Node *node) {
  if (node == NULL) {
    printf("-1\n");
    return;
  }

  printf("%d", node->data);

  if (node->left != NULL) {
    printf(" %d", node->left->data);
  }
  if (node->right != NULL) {
    printf(" %d", node->right->data);
  }

  printf("\n");
}

void destroyNode(Node *node) {
  if (node == NULL) {
    return;
  }
  destroyNode(node->left);
  destroyNode(node->right);
  free(node);
}

int main(void) {
  Node *folder8 = createNode(80, NULL, NULL);
  Node *folder7 = createNode(130, NULL, NULL);
  Node *folder6 = createNode(120, folder7, folder8);
  Node *folder5 = createNode(90, NULL, NULL);
  Node *folder4 = createNode(70, NULL, NULL);
  Node *folder3 = createNode(50, NULL, folder6);
  Node *folder2 = createNode(30, folder4, folder5);
  Node *folder1 = createNode(20, folder2, folder3);

  int folder_number;

  Node *folders[9] = {
    NULL,
    folder1,
    folder2,
    folder3,
    folder4,
    folder5,
    folder6,
    folder7,
    folder8
  };

  scanf("%d", &folder_number);

  if (folder_number < 1 || folder_number > 8) {
    printf("-1\n");
  } else {
    printNodeAndChildren(folders[folder_number]);
  }

  destroyNode(folder1);
  return 0;
}
