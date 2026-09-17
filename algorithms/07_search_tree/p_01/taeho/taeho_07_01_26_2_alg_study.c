#include <stdio.h>
#include <stdlib.h>
typedef struct tree_node{
    struct tree_node *parent;
    int key;
    struct tree_node *left_child;
    struct tree_node *right_child;
}N;
typedef struct tree {
    N *root;
    int size;
}T;
N* create_node(N *parent,int key) {
    N *node=malloc(sizeof(*node));
    if (!node) {
        printf("node malloc failed");
        exit(1);
    }
    node->parent=parent;
    node->key=key;
    node->left_child=NULL;
    node->right_child=NULL;
    return node;
}
T* create_tree() {
    T *tree=malloc(sizeof(*tree));
    if (!tree) {
        printf("tree malloc failed");
        exit(1);
    }
    tree->root=NULL;
    tree->size=0;
    return tree;
}
void free_all(N *node) {
    if (node) {
        free_all(node->left_child);
        free_all(node->right_child);
        free(node);
    }
}
N* find_element(T *tree,int key) {
    N *node=tree->root;
    while (node) {
        if (node->key<key) {
            if (node->right_child)node=node->right_child;
            else return node;///외부
        }
        else if (node->key>key){
            if (node->left_child)node=node->left_child;
            else return node;///외부
        }
        else return node;///발견
    }
}
void insertion_node(T *tree,int key) {
    if (!tree->root) {
        tree->root=create_node(NULL,key);
        return;
    }
    N *target=find_element(tree,key);
    if (target->key==key) {
        printf("node already exists");///문제에선 중복입력은 없다고 함
        return;
    }
    if (target->key<key) target->right_child=create_node(target,key);
    else target->left_child=create_node(target,key);
}
N* find_next_node(N *node) {
    node=node->right_child;///오른쪽 자식은 항상 존재
    while (node->left_child)node=node->left_child;
    return node;
}
int delete_node(T *tree,N *target) {
    int key=target->key;
    if (!target) {
        printf("target not found");
        return 0;
    }
    if (!target->left_child&&!target->right_child) {
        if (target->parent) {
            if (target->parent->left_child==target)target->parent->left_child=NULL;
            else target->parent->right_child=NULL;
        }
        else tree->root=NULL;
        free(target);
    }
    else if (target->left_child&&target->right_child) {
        target->key=delete_node(tree,find_next_node(target));
    }
    else {
        N *child=target->left_child?target->left_child:target->right_child;
        if (target->parent) {
            if (target->parent->left_child==target)target->parent->left_child=child;
            else target->parent->right_child=child;
        }
        else tree->root=child;
        child->parent=target->parent;
        free(target);
    }
    return key;
}
void print(N *node) {
    if (!node)return;
    printf(" %d",node->key);
    print(node->left_child);
    print(node->right_child);
}
int main() {
    setbuf(stdout,NULL);
    T *tree=create_tree();
    char input;
    int key;
    scanf("%d",&key);
    while (1) {
        scanf("%c",&input);
        if (input=='i') {
            scanf("%d",&key);
            insertion_node(tree,key);
        }
        else if (input=='d') {
            scanf("%d",&key);
            N *target=find_element(tree,key);
            if (target->key==key) {
                key=delete_node(tree,target);
                printf("%d",key);
            }
            else printf("X");
        }
        else if (input=='s') {
            scanf("%d",&key);
            N *target=find_element(tree,key);
            if (target->key!=key)printf("X");
            else printf("%d",target->key);
        }
        else if (input=='p') {
            print(tree->root);
        }
        else if (input=='q') break;
    }
    free_all(tree->root);
    return 0;
}