#include <stddef.h>
struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

struct TreeNode *lowestCommonAncestor(struct TreeNode *root, struct TreeNode *p, struct TreeNode *q) {
  if (root == NULL) {
    return NULL;
  }

  // p or q 발견 시
  if (root == p || root == q) {
    return root;
  }

  // 좌측 탐색
  struct TreeNode *left_result = lowestCommonAncestor(root->left, p, q);

  // 우측 탐색
  struct TreeNode *right_result = lowestCommonAncestor(root->right, p, q);

  // 1. 현재 노드 기준으로 p, q가 양쪽에서 발견된 경우 -> 현재 노드가 최소 조상
  if (left_result != NULL && right_result != NULL) {
    return root;
  }

  // 2. 왼쪽에서만 발견된 경우
  if (left_result != NULL) {
    return left_result;
  }

  // 3 오른쪽에서만 발견된 경우
  if (right_result != NULL) {
    return right_result;
  }

  return NULL;
}
