#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int id;
    int capacity;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createNode(int id, int capacity)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->id = id;
    newNode->capacity = capacity;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode *buildTree()
{
    TreeNode *root = createNode(1, 20);

    root->left = createNode(2, 30);
    // [수정됨] 중위 순회(50 130 120 80) 논리에 맞게 재배치
    root->right = createNode(3, 50);

    root->left->left = createNode(4, 70);
    root->left->right = createNode(5, 90);

    // [수정됨] F6과 F7의 올바른 용량
    root->right->right = createNode(6, 120);
    root->right->right->left = createNode(7, 130);
    root->right->right->right = createNode(8, 80);

    return root;
}

TreeNode *searchNode(TreeNode *root, int id)
{
    if (root == NULL)
        return NULL;
    if (root->id == id)
        return root;

    TreeNode *foundNode = searchNode(root->left, id);
    if (foundNode != NULL)
        return foundNode;

    return searchNode(root->right, id);
}

int total_sum = 0;

void traverseAndSum(TreeNode *root)
{
    if (root != NULL)
    {
        total_sum += root->capacity;
        traverseAndSum(root->left);
        traverseAndSum(root->right);
    }
}

void freeTree(TreeNode *root)
{
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main()
{
    TreeNode *root = buildTree();
    int target_id;

    if (scanf("%d", &target_id) == 1)
    {
        TreeNode *target_node = searchNode(root, target_id);

        if (target_node == NULL)
        {
            printf("-1\n");
        }
        else
        {
            total_sum = 0;
            traverseAndSum(target_node);
            printf("%d\n", total_sum);
        }
    }

    // [수정됨] 프로그램 종료 전 메모리 해제 함수 호출!
    freeTree(root);

    return 0;
}