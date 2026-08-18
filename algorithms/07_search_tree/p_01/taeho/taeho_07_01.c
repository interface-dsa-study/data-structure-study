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
    if (node&&node->key) {
        printf(" %d",node->key);
        if (node->left_child)print(node->left_child);
        if (node->right_child)print(node->right_child);
    }
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
        if (node->key>key)return node->key;
        if (right>key) return right;
    }
    return 0;
}
int remove_element(Node *loot_node,int key) {
    Node *target=search(loot_node,key);
    if (target->key==key) {
        int target_key=target->key;
        if (!target->left_child&&!target->right_child) {//자녀 0개
            if (target==loot_node) target->key=0;
            else {
                if (target->parent->left_child==target) target->parent->left_child=NULL;//부모 노드 자식 연결 수정
                else target->parent->right_child=NULL;
                free(target);
            }
        }
        else if (target->left_child&&!target->right_child||target->right_child&&!target->left_child) {//자녀 1개
            Node *child=target->left_child?target->left_child:target->right_child;
            if (target==loot_node) {
                if (child->left_child) {//자식 노드의 자식 노드들 연결
                    loot_node->left_child=child->left_child;
                    child->left_child->parent=loot_node;
                }
                if (child->right_child) {
                    loot_node->right_child=child->right_child;
                    child->right_child->parent=loot_node;
                }
                loot_node->key=child->key;// 키 연결(루트에 자식 노드를 덮어씌우는 느낌)
                free(child);
            }
            else {
                if (target->parent->left_child==target) target->parent->left_child=child;//부모 노드 자식 연결 수정
                else target->parent->right_child=child;
                child->parent=target->parent;
                free(target);
            }
        }
        else if (target->right_child&&target->left_child) {//자녀 2개
            target->key=remove_element(loot_node,search_next(loot_node,key));
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
    Node *loot_node=create_node(NULL,0);
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
            case 'd':
                scanf("%d",&key);
                int remove_result=remove_element(loot_node,key);
                if (remove_result==key) printf("%d",key);
                else printf("X");
                break;
            case 'p':
                print(loot_node);
                break;
        }
        if (input=='q')break;
        printf("\n");
    }
    free_node(loot_node);
    free(loot_node);
    return 0;
}