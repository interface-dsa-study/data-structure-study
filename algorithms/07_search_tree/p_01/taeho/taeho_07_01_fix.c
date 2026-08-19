#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    struct node *parent;
    int key;
    struct node *left_child;
    struct node *right_child;
}Node;
typedef struct tree {
    Node *root;
}Tree;
Node* create_external_node(Node *parent) {
    Node *new_node=malloc(sizeof(*new_node));
    if (!new_node) {
        fprintf(stderr,"node malloc failed");
        exit(1);
    }
    new_node->parent=parent;
    new_node->key=0;
    new_node->left_child=NULL;
    new_node->right_child=NULL;
    return new_node;
}
Node* create_internal_node(Node *parent,int key) {
    Node *new_node=malloc(sizeof(*new_node));
    if (!new_node) {
        fprintf(stderr,"node malloc failed");
        exit(1);
    }
    new_node->parent=parent;
    new_node->key=key;
    new_node->left_child=create_external_node(new_node);
    new_node->right_child=create_external_node(new_node);
    return new_node;
}
int is_external(Node *node) {
    return !node->left_child&&!node->right_child;
}
int is_internal(Node *node) {
    return !is_external(node);
}
void print(Node *node) {
    if (is_internal(node)) {
        printf(" %d",node->key);
        print(node->left_child);
        print(node->right_child);
    }
}
Node* tree_search(Tree *tree,int key) {
    Node *node=tree->root;
    while (is_internal(node)) {
        if (node->key<key) node=node->right_child;
        else if (node->key>key) node=node->left_child;
        else return node;
    }
    return node;
}
int find_element(Tree *tree,int key) {
    Node *node=tree->root;
    while (node&&node->key) {
        if (node->key<key&&node->right_child) node=node->right_child;
        else if (node->key>key&&node->left_child) node=node->left_child;
        else break;
    }
    return node->key;
}
void insert_item(Tree *tree,int key) {
    Node *node=tree_search(tree,key);
    if (is_internal(node)) {
        printf("node already exists");
        return;
    }
    Node *new_node=create_internal_node(node->parent,key);
    if (!node->parent) tree->root=new_node;
    else if (new_node->parent->key>key)new_node->parent->left_child=new_node;
    else new_node->parent->right_child=new_node;
    free(node);
}
Node* in_order_successor(Node *node) {//중위순회-> 키보다 큰 최소키 반환, 노드는 자식이 둘-> 오른쪽 자식 무조건 존재
    node=node->right_child;
    while (is_internal(node->left_child)) {
        node=node->left_child;
    }
    return node;
}
void free_node(Node *node) {
    if (is_external(node->left_child)&&is_external(node->right_child)){
        free(node->left_child);
        free(node->right_child);
        free(node);
    }
    else {
        printf("free_node() failed");
    }
}
int remove_element(Tree *tree,int key) {
    Node *target=tree_search(tree,key);
    if (target->key==key) {
        int target_key=target->key;
        if (is_external(target->left_child)&&is_external(target->right_child)) {//자녀 0개
            if (target==tree->root) {
                tree->root=create_external_node(NULL);
            }
            else {
                if (target->parent->key>key) target->parent->left_child=create_external_node(target->parent);//부모 노드 자식 연결 수정
                else target->parent->right_child=create_external_node(target->parent);
            }
            free_node(target);
        }
        else if ((is_internal(target->left_child)&&is_external(target->right_child))||(is_internal(target->right_child)&&is_external(target->left_child))) {//자녀 1개
            Node *child=target->left_child?target->left_child:target->right_child;
            if (target==tree->root) {
                tree->root=child;
                child->parent=NULL;
            }
            else {
                if (target->parent->key>key) target->parent->left_child=child;//부모 노드 자식 연결 수정
                else target->parent->right_child=child;
                child->parent=target->parent;
            }
            free_node(target);
        }
        else if (is_internal(target->right_child)&&is_internal(target->left_child)) { //자녀 2개
            Node *successor=in_order_successor(target);
            free(successor->left_child);//계승자->왼쪽 자식 없음(외부노드)-> 삭제
            successor->parent->left_child=successor->right_child;//계승자: 부모 노드의 왼쪽노드임-> 부모 노드와 계승자의 오른쪽 노드와 연결(오른쪽은 외부여도 무관)
            successor->right_child->parent=successor->parent;
            if (target==tree->root) successor->parent=NULL;//타겟이 루트면 타겟 부모 연결 X
            else {//타겟이 루트가 아니므로 타겟 부모 연결 필요
                successor->parent=target->parent;
                if (target->parent->key>key)target->parent->left_child=successor;
                else target->parent->right_child=successor;
            }
            successor->left_child=target->left_child;//계승자와 타겟 자식들 연결
            successor->right_child=target->right_child;
            free(target);
        }
        return target_key;
    }
    return 0;
}
void free_all_node(Node *node) {
    if (node) {
        free_all_node(node->left_child);
        free_all_node(node->right_child);
        free(node);
    }
}
int main() {
    setbuf(stdout,NULL);
    Tree *tree=malloc(sizeof(*tree));
    tree->root=create_external_node(NULL);
    while (1) {
        char input;
        int key;
        scanf(" %c",&input);
        switch (input) {
            case 'i':
                scanf("%d",&key);
                insert_item(tree,key);
                break;
            case 's':
                scanf("%d",&key);
                int search_result=find_element(tree,key);
                if (search_result==key) printf("%d",key);
                else printf("X");
                break;
            case 'd':
                scanf("%d",&key);
                int remove_result=remove_element(tree,key);
                if (remove_result==key) printf("%d",key);
                else printf("X");
                break;
            case 'p':
                print(tree->root);
                break;
        }
        if (input=='q')break;
        printf("\n");
    }
    free_all_node(tree->root);
    return 0;
}