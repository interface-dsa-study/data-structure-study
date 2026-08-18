#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>

typedef struct TreeNode {
    int key;
    struct TreeNode* lChild;
    struct TreeNode* rChild;
    struct TreeNode* parent;
}TreeNode;

void insertItem(TreeNode** root, int k) {
    TreeNode* newnode = malloc(sizeof(TreeNode));
    newnode->key = k;
    newnode->parent = NULL;
    newnode->lChild = NULL;
    newnode->rChild = NULL;
    if (*root == NULL) {
        *root = newnode;
    }
    else {
        TreeNode* temp = *root;
        while (1) {
            if (temp->key > k) {
                if (temp->lChild == NULL) {
                    newnode->parent = temp;
                    temp->lChild = newnode;
                    return;
                }
                temp = temp->lChild;
            }
            else {
                if (temp->rChild == NULL) {
                    newnode->parent = temp;
                    temp->rChild = newnode;
                    return;
                }
                temp = temp->rChild;
            }
        }
    }
}

int findElement(TreeNode* root, int k) {
    int findkey;
    if (root == NULL) {
        return 0;
    }
    if (root->key == k) {
        return k;
    }
    findkey = findElement(root->lChild, k);
    if (findkey) {
        return k;
    }
    return findElement(root->rChild, k);
}

TreeNode* TreeSearch(TreeNode* root, int k) {
    if (root == NULL) {
        return NULL;
    }
    if (root->key == k) {
        return root;
    }
    TreeNode* findnode = TreeSearch(root->lChild, k);
    if (findnode) {
        return findnode;
    }
    return TreeSearch(root->rChild, k);
}

bool isExternal(TreeNode* root) {
    if (root->rChild == NULL || root->lChild == NULL) {
        return true;
    }
    return false;
}

TreeNode* inOrderSucc(TreeNode* node) {
    node = node->rChild;
    while (node->lChild) {
        node = node->lChild;
    }
    return node;
}

void removeElement(TreeNode* root, int k) {
    TreeNode* findnode = TreeSearch(root, k);
    if (findnode == NULL) {
        printf("X\n");
        return;
    }
    else {
        printf("%d\n", findnode->key);
        if (isExternal(findnode)) {
            if (findnode->rChild == NULL && findnode->lChild == NULL) {
                if (findnode->parent->lChild == findnode) {
                    findnode->parent->lChild = NULL;
                }
                else {
                    findnode->parent->rChild = NULL;
                }
            }
            else {
                TreeNode* successor = findnode->lChild == NULL ? findnode->rChild : findnode->lChild;
                if (findnode->parent->lChild == findnode) { //부모가 루트일 때 고려해야 함
                    findnode->parent->lChild = successor;
                    successor->parent = findnode->parent;
                }
                else {
                    findnode->parent->rChild = successor;
                    successor->parent = findnode->parent;
                }
            }
            free(findnode);
            findnode = NULL;
        }
        else {
            TreeNode* successor = inOrderSucc(findnode);
            printf("|%d %d|", findnode->key, successor->key);
            if (successor->rChild != NULL) {
                successor->parent->lChild = successor->rChild;
                successor->rChild->parent = successor->parent;
            }
            findnode->key = successor->key;
            free(successor);
            successor = NULL;
        }
    }
}

void preorder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printf(" %d", root->key);
    preorder(root->lChild);
    preorder(root->rChild);
}

int main() {
    TreeNode* BST = NULL;
    char ch;
    int key;

    while (1) {
        scanf(" %c", &ch);
        if (ch == 'q') {
            break;
        }
        if (ch == 'i') {
            scanf("%d", &key);
            insertItem(&BST, key);
        }
        else if (ch == 'd') {
            scanf("%d", &key);
            removeElement(BST, key);
        }
        else if (ch == 's') {
            scanf("%d", &key);
            int findkey = findElement(BST, key);
            if (findkey) {
                printf("%d\n", findkey);
            }
            else {
                printf("X");
            }
        }
        else {
            preorder(BST);
            printf("\n");
        }
    }

    return 0;
}