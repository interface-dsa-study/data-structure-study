#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode {
  struct TreeNode *left;
  int node_number;
  struct TreeNode *right;
} TreeNode;

TreeNode *createTreeNode(int node_number) {
  TreeNode *tree_node = malloc(sizeof(*tree_node));
  if (tree_node == NULL) {
    exit(EXIT_FAILURE);
  }
  tree_node->node_number = node_number;
  tree_node->left = NULL;
  tree_node->right = NULL;
  return tree_node;
}

void destroyTreeNode(TreeNode *tree_node) {
  if (tree_node == NULL) {
    return;
  }
  destroyTreeNode(tree_node->left);
  destroyTreeNode(tree_node->right);
  free(tree_node);
}

TreeNode *findTreeNodeByNodeNumber(TreeNode *tree_node, int node_number) {
  if (tree_node == NULL) {
    return NULL;
  }
}

int main(void) {
  int node_count;
  int root_node, left_node, right_node;
  scanf("%d", &node_count);

  for (int i = 0; i < node_count; i++) {
    scanf("%d %d %d", &root_node, &left_node, &right_node);
  }
}
