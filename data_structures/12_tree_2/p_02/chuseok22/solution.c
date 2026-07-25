#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode {
  struct TreeNode *left;
  struct TreeNode *right;
  int id;
  int data;
} TreeNode;

TreeNode *createTreeNode(int id, int data, TreeNode *left, TreeNode *right) {
  TreeNode *tree_node = malloc(sizeof(*tree_node));
  if (tree_node == NULL) {
    exit(EXIT_FAILURE);
  }
  tree_node->id = id;
  tree_node->data = data;
  tree_node->left = left;
  tree_node->right = right;
  return tree_node;
}

TreeNode *createExampleTreeNode(void) {
  TreeNode *tree_node_8 = createTreeNode(8, 80, NULL, NULL);
  TreeNode *tree_node_7 = createTreeNode(7, 130, NULL, NULL);
  TreeNode *tree_node_6 = createTreeNode(6, 120, tree_node_7, tree_node_8);
  TreeNode *tree_node_5 = createTreeNode(5, 90, NULL, NULL);
  TreeNode *tree_node_4 = createTreeNode(4, 70, NULL, NULL);
  TreeNode *tree_node_3 = createTreeNode(3, 50, NULL, tree_node_6);
  TreeNode *tree_node_2 = createTreeNode(2, 30, tree_node_4, tree_node_5);
  TreeNode *tree_node_1 = createTreeNode(1, 20, tree_node_2, tree_node_3);
  return tree_node_1;
}

void destroyTreeNode(TreeNode *tree_node) {
  if (tree_node == NULL) {
    return;
  }
  destroyTreeNode(tree_node->left);
  destroyTreeNode(tree_node->right);
  free(tree_node);
}

TreeNode *findTreeNodeById(TreeNode *tree_node, int id) {
  if (tree_node == NULL) {
    return NULL;
  }

  if (tree_node->id == id) {
    return tree_node;
  }

  TreeNode *found_tree_node = findTreeNodeById(tree_node->left, id);
  if (found_tree_node != NULL) {
    return found_tree_node;
  }

  return findTreeNodeById(tree_node->right, id);
}

int calculateSubtreeNode(TreeNode *tree_node) {
  if (tree_node == NULL) {
    return 0;
  }
  return tree_node->data + calculateSubtreeNode(tree_node->left) + calculateSubtreeNode(tree_node->right);
}

int main(void) {
  int node_id;

  scanf("%d", &node_id);
  TreeNode *tree_node = createExampleTreeNode();

  TreeNode *target_tree_node = findTreeNodeById(tree_node, node_id);
  if (target_tree_node == NULL) {
    printf("-1\n");
    destroyTreeNode(tree_node);
    return 0;
  }

  int result = calculateSubtreeNode(target_tree_node);
  printf("%d\n", result);
  destroyTreeNode(tree_node);
  return 0;
}
