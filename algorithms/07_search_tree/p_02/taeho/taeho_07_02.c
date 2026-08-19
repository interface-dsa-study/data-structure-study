#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    struct node *parent;
    int height;
    int key;
    struct node *left_child;
    struct node *right_child;
}Node;
Node* create_node(Node *parent,int height,int key) {
    Node *node=malloc(sizeof(*node));
    if (!node) {
        fprintf(stderr,"node malloc failed");
        exit(1);
    }
    node->parent=parent;
    node->height=height;
    node->key=key;
    node->left_child=NULL;
    node->right_child=NULL;
    return node;
}
Node* search(Node *loot_node,int key) {
    Node *node=loot_node;
    while(1) {
        if (node->key<key&&node->right_child)node=node->right_child;
        else if (node->key>key&&node->left_child)node=node->left_child;
        else break;
    }
    return node;
}
void restruct(Node *x,Node *y,Node *z) {
    if (x->left_child==y)
}
int update_height(Node *node) {
    if (!node->left_child&&!node->right_child) node->height=1;
    else {
        int left=0,right=0;
        if (node->left_child)left=update_height(node->left_child);
        if (node->right_child)right=update_height(node->right_child);
        node->height=left<right?right:left;
        node->height++;
    }
    return node->height;
}
int is_balanced(Node *loot_node) {

}
void search_and_fix(Node *loot_node) {
    update_height(loot_node);
}
void insert_item(Node *loot_node,int key) {
    if (!loot_node->key) {
        loot_node->height=1;
        loot_node->key=key;
    }
    else {
        Node *node=search(loot_node,key);
        if (node->key<key&&!node->right_child)node->right_child=create_node(node,1,key);
        else if (node->key>key&&!node->left_child)node->left_child=create_node(node,1,key);
        else printf("insert failed");
    }
}
void print(Node *node) {
    if (node) {
        printf(" %d",node->key);
        if (node->left_child)print(node->left_child);
        if (node->right_child)print(node->right_child);
    }
}
void free_node(Node *node) {
    if (node) {
        free_node(node->left_child);
        free_node(node->right_child);
        free(node);
    }
}
int main() {
    setbuf(stdout,NULL);
    Node *loot_node=create_node(NULL,0,0);
    while (1) {
        char input;
        int key;
        scanf(" %c",&input);
        switch (input) {
            case 'i':
                scanf("%d",&key);
                insert_item(loot_node,key);
                break;
            case 's':
                scanf("%d",&key);
                int search_result=search(loot_node,key)->key;
                if (search_result==key) printf("%d",key);
                else printf("X");
                break;
            case 'p':
                print(loot_node);
                break;
        }
        if (input=='q')break;
    }
    free_node(loot_node);
}