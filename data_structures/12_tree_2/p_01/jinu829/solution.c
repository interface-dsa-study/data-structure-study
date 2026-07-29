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
    TreeNode *n1 = createNode(1, 20);
    TreeNode *n2 = createNode(2, 30);
    TreeNode *n3 = createNode(3, 50);
    TreeNode *n4 = createNode(4, 70);
    TreeNode *n5 = createNode(5, 90);
    TreeNode *n6 = createNode(6, 120);
    TreeNode *n7 = createNode(7, 130);
    TreeNode *n8 = createNode(8, 80);

    n1->left = n2;
    n1->right = n3;

    n2->left = n4;
    n2->right = n5;

    n3->right = n6;
    n6->left = n7;
    n6->right = n8;

    return n1;
}

TreeNode *searchNode(TreeNode *root, int targetId)
{
    if (root == NULL)
        return NULL;
    if (root->id == targetId)
        return root;

    TreeNode *leftResult = searchNode(root->left, targetId);
    if (leftResult != NULL)
        return leftResult;

    return searchNode(root->right, targetId);
}

void printNode(TreeNode *node)
{
    printf(" %d", node->capacity);
}

void preOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    printNode(root);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    inOrder(root->left);
    printNode(root);
    inOrder(root->right);
}

void postOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    postOrder(root->left);
    postOrder(root->right);
    printNode(root);
}

int getCapacitySum(TreeNode *root)
{
    if (root == NULL)
        return 0;
    return root->capacity + getCapacitySum(root->left) + getCapacitySum(root->right);
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
    int menu = 1;

    if (menu == 1)
    {
        int traversalType, targetId;
        if (scanf("%d %d", &traversalType, &targetId) == 2)
        {
            TreeNode *target = searchNode(root, targetId);

            if (target == NULL)
            {
                printf("-1\n");
            }
            else
            {
                if (traversalType == 1)
                    preOrder(target);
                else if (traversalType == 2)
                    inOrder(target);
                else if (traversalType == 3)
                    postOrder(target);
                printf("\n");
            }
        }
    }
    else if (menu == 2)
    {
        int targetId;
        if (scanf("%d", &targetId) == 1)
        {
            TreeNode *target = searchNode(root, targetId);

            if (target == NULL)
            {
                printf("-1\n");
            }
            else
            {
                int sum = getCapacitySum(target);
                printf("%d\n", sum);
            }
        }
    }

    freeTree(root);
    return 0;
}
