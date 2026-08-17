#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    struct node *parent;
    int key;
    struct node *left_child;
    struct node *right_child;
}Node;
Node* create_node(Node *parent,int key) {
    Node *new_node=malloc(sizeof(*new_node));
    if (!new_node) {
        fprintf(stderr,"node malloc failed");
        exit(1);
    }
    new_node->parent=parent;
    new_node->key=key;
    new_node->left_child=NULL;
    new_node->right_child=NULL;
    return new_node;
}
void print(Node *node) {
    if (node&&node->key)printf(" %d",node->key);
    if (node->left_child)print(node->left_child);
    if (node->right_child)print(node->right_child);
}
Node* search(Node *loot_node,int key) {
    Node *node=loot_node;
    while (node) {
        if (node->key<key&&node->right_child) node=node->right_child;
        else if (node->key>key&&node->left_child) node=node->left_child;
        else break;
    }
    return node;
}
void insert_item(Node *loot_node,int key) {
    if (!loot_node->key) loot_node->key=key;
    else {
        Node *node=search(loot_node,key);
        if (node->key>key&&!node->left_child)node->left_child=create_node(node,key);
        else if (node->key<key&&!node->right_child)node->right_child=create_node(node,key);
        else printf("insert failed");
    }
}
int search_next(Node *node,int key) {//중위순회-> 키보다 큰 최소키 반환
    if (node) {
        int left=search_next(node->left_child,key);
        int right=search_next(node->right_child,key);
        if (left>key)return left;
        else if (node->key>key)return node->key;
        else if (right>key) return right;
    }
    return 0;
}
int remove_element(Node *loot_node,int key) {
    Node *target_node=search(loot_node,key);
    if (target_node->key==key) {
        int target_key=target_node->key;
        if (!target_node->left_child&&!target_node->right_child) {//자녀 0개
            if (target_node==loot_node) {
                target_node->key=0;
            }
            else {
                if (target_node->parent->left_child==target_node) target_node->parent->left_child=NULL;//부모 노드 자식 연결 수정
                else target_node->parent->right_child=NULL;
                free(target_node);
            }
        }
        else if (target_node->left_child&&!target_node->right_child||target_node->right_child&&!target_node->left_child) {//자녀 1개
            Node *child=target_node->left_child?target_node->left_child:target_node->right_child;
            if (target_node!=loot_node) {
                if (target_node->parent->left_child==target_node) target_node->parent->left_child=child;//부모 노드 자식 연결 수정
                else target_node->parent->right_child=child;
                child->parent=target_node->parent;
            }
            else {
                loot_node->key=remove_element(loot_node,child->key);

            }
            free(target_node);
        }
        else if (target_node->right_child&&target_node->left_child) {//자녀 2개
            target_node->key=remove_element(loot_node,search_next(loot_node,key));
        }
        return target_key;
    }
    return 0;
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
    Node *tree=create_node(NULL,0);
    while (1) {
        char input;
        int key;
        scanf(" %c",&input);
        if (input=='i'||input=='d'||input=='s') scanf("%d",&key);
        if (input=='i')insert_item(tree,key);
        else if (input=='d')printf(" %d",remove_element(tree,key));
        else if (input=='s') {
            Node *search_result=search(tree,key);
            if (search_result->key==key)printf(" %d",key);
            else printf("X");
        }
        else if (input=='p')print(tree);
        else if (input=='q')break;
        printf("\n");
    }
    free_node(tree);
    free(tree);
    return 0;
}