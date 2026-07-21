#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct TreeNode{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

TreeNode* make_node(int num) {
    TreeNode* newnode = malloc(sizeof(TreeNode));
    newnode->data = num;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

TreeNode* findnode(TreeNode* root, int num) {
    TreeNode* temp;
    if (root == NULL) {
        return NULL;
    }
    else {
        if (root->data == num) {
            return root;
        }
        temp = findnode(root->left, num);
        if (temp) {
            return temp;
        }
        temp = findnode(root->right, num);
        if (temp) {
            return temp;
        }
    }
}

void make_Tree(TreeNode** root, int Num, int leftnum, int rightnum) {
    if (*root == NULL) {
        *root = make_node(Num);
        (*root)->left = leftnum != 0 ? make_node(leftnum) : NULL;
        (*root)->right = rightnum != 0 ? make_node(rightnum) : NULL;
        return;
    }
    else {
        TreeNode* parent = findnode(*root, Num);
        parent->left = leftnum != 0 ? make_node(leftnum) : NULL;
        parent->right = rightnum != 0 ? make_node(rightnum) : NULL;
    }

    return 0;
}


void Print(TreeNode* root, char s[], int len) {
    if (s[len] == '\0' || root == NULL) {
        printf(" %d", root->data);
        return;
    }
    else {
        printf(" %d", root->data);
        if (s[len] == 'R') {
            Print(root->right, s, len+1);
        }
        else {
            Print(root->left, s, len+1);
        }
    }

}

void Preorder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printf("| %d|", root->data);
    Preorder(root->left);
    Preorder(root->right);
}

int main() {
    TreeNode *Tree = NULL;
    int Num, rightnum, leftnum, N, i, len;
    char c[101];

    scanf("%d", &N);

    for (i = 0;i < N;i++) {
        scanf("%d %d %d", &Num, &leftnum, &rightnum);
        make_Tree(&Tree, Num, leftnum, rightnum);

    }

    scanf("%d", &N);

    getchar();

    for (i = 0;i < N;i++) {
        scanf("%s", c);
        len = 0;
        Print(Tree, c, len);
        printf("\n");
    }

    return 0;
}