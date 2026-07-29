#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
}Node;

void initNode(Node *root) {
    root->left = NULL;
    root->right = NULL;
    root = NULL;
}

void CreateTree(Node *root) {
    initNode(root);
    Node *f1, *f2, *f3, *f4, *f5, *f6, *f7, *f8;
    f1->data = 20; f2->data = 30; f3->data = 50; f4->data = 70; f5->data = 90; f6->data = 120; f7->data = 130; f8->data = 80;
    root = f1; f1->left = f2; f1->right = f3;
    f2->left = f4; f2->right = f5;
    f3->right = f6;
    f6->left = f7; f6->right = f8;
};

int main(void) {
    int N; scanf("%d", &N); // 노드 번호 입력
    
}