#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct TreeNode{
    int data;
    int id;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

void make_Tree(TreeNode** root, int data, int id) {
    TreeNode* newnode = malloc(sizeof(TreeNode));
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->data = data;
    newnode->id = id;
    *root = newnode;
}

TreeNode* findnode(TreeNode* root, int id) {
    TreeNode* temp = root;
    TreeNode* check1;
    if (temp == NULL) {
        return temp;
    }
    else {
        if (temp->id == id) {
            return temp;
        }
        else {
            check1 = findnode(temp->left, id);
            if (check1 != NULL) {
                return check1;
            }
            check1 = findnode(temp->right, id);
            if (check1 != NULL) {
                return check1;
            }
        }
    }

}

void Preorder_Traversal(TreeNode* root) { // 선위순회
    TreeNode* temp = root;
    if (temp == NULL) {
        return;
    }
    printf(" %d", temp->data);
    Preorder_Traversal(temp->left);
    Preorder_Traversal(temp->right);
}

void Inorder_Traversal(TreeNode* root) { // 중위순회
    TreeNode* temp = root;
    if (temp == NULL) {
        return;
    }
    Inorder_Traversal(temp->left);
    printf(" %d", temp->data);
    Inorder_Traversal(temp->right);
}

void Postorder_Traversal(TreeNode* root) { // 후위순회
    TreeNode* temp = root;
    if (temp == NULL) {
        return;
    }
    Postorder_Traversal(temp->left);
    Postorder_Traversal(temp->right);
    printf(" %d", temp->data);
}

int main() {
    TreeNode *Tree = NULL;
    TreeNode* fnode = NULL;
    int Num, nodeid;
    make_Tree(&Tree, 20, 1);
    make_Tree(&Tree->left, 30, 2);
    make_Tree(&Tree->right, 50, 3);
    make_Tree(&Tree->left->left, 70, 4);
    make_Tree(&Tree->left->right, 90, 5);
    make_Tree(&Tree->right->right, 120, 6);
    Tree->right->left = NULL;
    make_Tree(&Tree->right->right->left, 130, 7);
    make_Tree(&Tree->right->right->right, 80, 8);

    scanf("%d %d", &Num, &nodeid);

    fnode = findnode(Tree, nodeid);

    if (nodeid >= 9) {
        printf("-1");
    }
    else {
        if (Num == 1) {
            Preorder_Traversal(fnode);
        }
        else if (Num == 2) {
            Inorder_Traversal(fnode);
        }
        else if (Num == 3) {
            Postorder_Traversal(fnode);
        }
    }

    return 0;
}