#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode {
  int id;
  int data;
  struct TreeNode *left;
  struct TreeNode *right;
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

TreeNode *createFixedTreeNode(void) {
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

TreeNode *findTreeNodeById(TreeNode *tree_node, int target_id) {
  if (tree_node == NULL) {
    return NULL;
  }

  if (tree_node->id == target_id) {
    return tree_node;
  }

  TreeNode *found_node = findTreeNodeById(tree_node->left, target_id);

  if (found_node != NULL) {
    return found_node;
  }

  return findTreeNodeById(tree_node->right, target_id);
}

void preorderTraversal(TreeNode *tree_node) {
  if (tree_node == NULL) {
    return;
  }

  printf(" %d", tree_node->data);

  preorderTraversal(tree_node->left);
  preorderTraversal(tree_node->right);
}

void inorderTraversal(TreeNode *tree_node) {
  if (tree_node == NULL) {
    return;
  }

  inorderTraversal(tree_node->left);

  printf(" %d", tree_node->data);

  inorderTraversal(tree_node->right);
}

void postorderTraversal(TreeNode *tree_node) {
  if (tree_node == NULL) {
    return;
  }

  postorderTraversal(tree_node->left);
  postorderTraversal(tree_node->right);
  printf(" %d", tree_node->data);
}

int main(void) {
  int traversal_type, target_node_id;

  scanf("%d %d", &traversal_type, &target_node_id);

  TreeNode *tree_node = createFixedTreeNode();
  TreeNode *target_tree_node = findTreeNodeById(tree_node, target_node_id);

  if (target_tree_node == NULL) {
    printf("-1\n");
    destroyTreeNode(tree_node);
    return 0;
  }

  switch (traversal_type) {
    case 1:
      preorderTraversal(target_tree_node);
      break;
    case 2:
      inorderTraversal(target_tree_node);
      break;
    case 3:
      postorderTraversal(target_tree_node);
      break;
    default:
      printf("-1\n");
  }

  destroyTreeNode(tree_node);
  return 0;
}
