#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *parent;
    int key;
    struct node *left_child;
    struct node *right_child;
} Node;

typedef struct tree {
    Node *root;
} Tree;


/* 외부노드 생성 */
Node *create_external_node(Node *parent) {
    Node *new_node = malloc(sizeof(*new_node));

    if (new_node == NULL) {
        fprintf(stderr, "node malloc failed\n");
        exit(1);
    }

    new_node->parent = parent;
    new_node->key = 0;
    new_node->left_child = NULL;
    new_node->right_child = NULL;

    return new_node;
}


/* 내부노드 생성 */
Node *create_internal_node(Node *parent, int key) {
    Node *new_node = malloc(sizeof(*new_node));

    if (new_node == NULL) {
        fprintf(stderr, "node malloc failed\n");
        exit(1);
    }

    new_node->parent = parent;
    new_node->key = key;

    new_node->left_child = create_external_node(new_node);
    new_node->right_child = create_external_node(new_node);

    return new_node;
}


/* 외부노드인지 확인 */
int is_external(Node *node) {
    return node->left_child == NULL &&
           node->right_child == NULL;
}


/* 내부노드인지 확인 */
int is_internal(Node *node) {
    return !is_external(node);
}


/* 전위순회 */
void print(Node *node) {
    if (is_internal(node)) {
        printf(" %d", node->key);

        print(node->left_child);
        print(node->right_child);
    }
}


/* 탐색
   찾으면 해당 내부노드 반환
   못 찾으면 해당 위치의 외부노드 반환
*/
Node *tree_search(Tree *tree, int key) {
    Node *node = tree->root;

    while (is_internal(node)) {

        if (key == node->key)
            return node;

        else if (key < node->key)
            node = node->left_child;

        else
            node = node->right_child;
    }

    return node;
}


/* 탐색 명령 */
int find_element(Tree *tree, int key) {
    Node *node = tree_search(tree, key);

    if (is_external(node))
        return -1;

    return node->key;
}


/* 삽입 */
void insert_item(Tree *tree, int key) {
    Node *node = tree_search(tree, key);

    /* 중복 키는 없다고 가정 */
    if (is_internal(node))
        return;

    /*
        node는 삽입될 위치의 외부노드
    */
    Node *new_node = create_internal_node(node->parent, key);

    /* 현재 트리가 빈 트리 */
    if (node->parent == NULL) {
        tree->root = new_node;
    }

    /* 부모의 왼쪽에 삽입 */
    else if (node->parent->left_child == node) {
        node->parent->left_child = new_node;
    }

    /* 부모의 오른쪽에 삽입 */
    else {
        node->parent->right_child = new_node;
    }

    /* 기존 외부노드 제거 */
    free(node);
}


/* 중위순회 후계자 */
Node *in_order_successor(Node *node) {

    /*
        오른쪽 자식으로 이동
    */
    Node *successor = node->right_child;

    /*
        왼쪽 자식이 내부노드인 동안 계속 이동
    */
    while (is_internal(successor->left_child)) {
        successor = successor->left_child;
    }

    return successor;
}


/*
    외부노드 z를 제거하고
    z의 형제 노드가 z의 부모 자리를 계승하도록 함

              g
              |
              w
             / \
            z   zs

        ↓

              g
              |
             zs
*/
Node *reduce_external(Tree *tree, Node *z) {

    Node *w = z->parent;
    Node *zs;

    /* z의 형제 찾기 */
    if (w->left_child == z)
        zs = w->right_child;
    else
        zs = w->left_child;


    /* w가 루트인 경우 */
    if (w == tree->root) {

        tree->root = zs;
        zs->parent = NULL;
    }

    /* w가 루트가 아닌 경우 */
    else {

        Node *g = w->parent;

        zs->parent = g;

        if (g->left_child == w)
            g->left_child = zs;
        else
            g->right_child = zs;
    }

    /*
        z : 외부노드
        w : 삭제할 내부노드
    */
    free(z);
    free(w);

    return zs;
}


/* 삭제 */
int remove_element(Tree *tree, int key) {

    Node *target = tree_search(tree, key);

    /* 키가 존재하지 않음 */
    if (is_external(target))
        return -1;

    int deleted_key = target->key;


    /*
        CASE 1
        왼쪽 자식이 외부노드

        자식이 0개인 경우도 포함
        자식이 오른쪽에 1개 있는 경우도 포함
    */
    if (is_external(target->left_child)) {

        reduce_external(tree, target->left_child);
    }


    /*
        CASE 2
        오른쪽 자식이 외부노드

        자식이 왼쪽에 1개 있는 경우
    */
    else if (is_external(target->right_child)) {

        reduce_external(tree, target->right_child);
    }


    /*
        CASE 3
        자식이 둘 다 내부노드

        중위순회 후계자를 찾아
        key만 복사한 뒤
        후계자를 삭제
    */
    else {

        Node *successor = in_order_successor(target);

        /*
            후계자의 key를 target으로 복사
        */
        target->key = successor->key;

        /*
            successor의 왼쪽은 반드시 외부노드
        */
        reduce_external(tree, successor->left_child);
    }

    return deleted_key;
}


/* 트리 전체 메모리 해제 */
void free_all_node(Node *node) {

    if (node == NULL)
        return;

    free_all_node(node->left_child);
    free_all_node(node->right_child);

    free(node);
}


/* main */
int main() {

    setbuf(stdout, NULL);

    Tree *tree = malloc(sizeof(*tree));

    if (tree == NULL) {
        fprintf(stderr, "tree malloc failed\n");
        exit(1);
    }

    /*
        빈 BST

        root 하나만 존재하며
        root는 외부노드
    */
    tree->root = create_external_node(NULL);


    while (1) {

        char input;
        int key;

        scanf(" %c", &input);


        switch (input) {

            /* 삽입 */
            case 'i':

                scanf("%d", &key);

                insert_item(tree, key);

                break;


            /* 탐색 */
            case 's': {

                scanf("%d", &key);

                int result = find_element(tree, key);

                if (result == key)
                    printf("%d", result);
                else
                    printf("X");

                break;
            }


            /* 삭제 */
            case 'd': {

                scanf("%d", &key);

                int result = remove_element(tree, key);

                if (result == key)
                    printf("%d", result);
                else
                    printf("X");

                break;
            }


            /* 전위순회 */
            case 'p':

                print(tree->root);

                break;


            /* 종료 */
            case 'q':

                free_all_node(tree->root);
                free(tree);

                return 0;
        }

        printf("\n");
    }
}