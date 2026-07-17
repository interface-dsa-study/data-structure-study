#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct TreeNode{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

void make_tree(TreeNode** Node, int data, TreeNode* left, TreeNode* right) {
    TreeNode* newnode = (TreeNode*)malloc(sizeof(TreeNode));
    newnode->data = data;
    newnode->right = right;
    newnode->left = left;
    (*Node) = newnode;
}

int main() {
    TreeNode *Tree[8];
    int Num;
    make_tree(&Tree[7], 80, NULL, NULL);
    make_tree(&Tree[6], 130, NULL, NULL);
    make_tree(&Tree[5], 120, Tree[6], Tree[7]);
    make_tree(&Tree[4], 90, NULL, NULL);
    make_tree(&Tree[3], 70, NULL, NULL);
    make_tree(&Tree[2], 50, NULL, Tree[5]);
    make_tree(&Tree[1], 30, Tree[3], Tree[4]);
    make_tree(&Tree[0], 20, Tree[1], Tree[2]);

    scanf("%d", &Num);

    if (Num - 1 >= 8) {
        printf("-1");
    }
    else {
        printf("%d", Tree[Num-1]->data);
        if (Tree[Num - 1]->left != NULL) {
            printf(" %d", Tree[Num - 1]->left->data);
        }
        if (Tree[Num - 1]->right != NULL) {
            printf(" %d", Tree[Num - 1]->right->data);
        }
    }

    return 0;
}