#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* create_node(int data, TreeNode *left, TreeNode *right) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = left;
    node->right = right;
    return node;
}

int main() {
    // 단말 노드부터 생성
    TreeNode *F4 = create_node(70, NULL, NULL);
    TreeNode *F5 = create_node(90, NULL, NULL);
    TreeNode *F7 = create_node(130, NULL, NULL);
    TreeNode *F8 = create_node(80, NULL, NULL);
    
    // 부모 노드 생성
    TreeNode *F2 = create_node(30, F4, F5);
    TreeNode *F6 = create_node(120, F7, F8);
    TreeNode *F3 = create_node(50, NULL, F6);
    
    // 루트 노드 생성
    TreeNode *F1 = create_node(20, F2, F3);
    
    // 포인터 배열을 통해 노드 접근 용이하게 함
    TreeNode* nodes[10] = {NULL, F1, F2, F3, F4, F5, F6, F7, F8, NULL};
    
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    if (n < 1 || n > 8 || nodes[n] == NULL) {
        printf("-1\n");
    } else {
        TreeNode *target = nodes[n];
        printf("%d", target->data);
        if (target->left != NULL) {
            printf(" %d", target->left->data);
        }
        if (target->right != NULL) {
            printf(" %d", target->right->data);
        }
        printf("\n");
    }
    
    // 메모리 해제 (실제로는 프로그램 종료 시 해제되지만 명시적으로 작성)
    free(F1); free(F2); free(F3); free(F4); free(F5); free(F6); free(F7); free(F8);
    
    return 0;
}