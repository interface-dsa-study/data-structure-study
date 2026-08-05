#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
    struct node *left;
    int data;
    struct node *right;
}Node;
Node* create_node(int data) {
    Node *node=(Node*)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr,"node malloc failed");
        exit(1);
    }
    node->data=data;
    node->left=NULL;
    node->right=NULL;
    return node;
}
Node *search_data(Node *node,int data) {
    if (node) {
        if (node->data==data) return node;
        Node *left=search_data(node->left,data);
        if (left) return left;
        Node *right=search_data(node->right,data);
        if (right) return right;
    }
    return NULL;
}
Node* tree_create() {
    Node *loot_node=NULL;
    int tree_size;
    scanf("%d",&tree_size);
    Node *node=NULL;
    for (int i=0;i<tree_size;i++) {
        int node_data;
        int node_left_data;
        int node_right_data;
        scanf("%d %d %d",&node_data,&node_left_data,&node_right_data);
        node=search_data(loot_node,node_data);
        if (!node) node=create_node(node_data);
        if (!i)loot_node=node;
        node->data=node_data;
        if (node_left_data) {
            node->left=create_node(node_left_data);
        }
        if (node_right_data) {
            node->right=create_node(node_right_data);
        }
    }
    return loot_node;
}
void search(Node *loot_node) {
    int time;
    scanf("%d",&time);
    for (int i=0;i<time;i++) {
        Node *pointer=loot_node;
        char string[100]={0};
        scanf("%s",string);
        printf(" %d",pointer->data);
        for (int j=0;j<strlen(string);j++) {
            switch (string[j]) {
                case 'R':
                    if (pointer->right) pointer=pointer->right;
                    break;
                case 'L':
                    if (pointer->left) pointer=pointer->left;
                    break;
            }
            printf(" %d",pointer->data);
        }
        printf("\n");
    }
}
void free_binomial_tree_node(Node *node) {
    if (node->left) free_binomial_tree_node(node->left);
    if (node->right) free_binomial_tree_node(node->right);
    if (node) free(node);
}
int main() {
    Node *loot_node=tree_create();
    search(loot_node);
    free_binomial_tree_node(loot_node);
    return 0;
}