#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int key;
    struct Node *next;
}Node;

Node *createNode(int key){
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->key = key;
    return new_node;
}

void insertItem(int key, Node *arr, int M){
    Node *insert_node = createNode(key);
    //printf("%d\n", insert_node->key);
    int v = key % M;
    insert_node->next = arr[v].next;
    arr[v].next = insert_node;
    printf("%d\n", arr[v].next->key);
}

int deleteItem(int key, Node *arr, int M){
    int v = key % M;
    Node *delete_Node = arr[v].next;
    if (delete_Node->key == key){
        arr[v].next = delete_Node->next;
        free(delete_Node);
        return 1;
    }
    while (delete_Node->next != NULL){
        if (delete_Node->next->key == key){
            delete_Node->next = delete_Node->next->next;
            free(delete_Node->next);
            return 1;
        }
    }
    return 0;
}

int findElement(int k, Node *arr, int M){
    int v = k % M;
    Node *search_Node = arr[v].next;
    while (search_Node->next != NULL){
        if (search_Node->key == k)
            return 1;
        search_Node = search_Node->next;
    }
    return 0;
}

void print(Node *arr, int M){
    Node *print_Node;
    for (int i = 0; i < M; i++){
        print_Node = arr[i].next;
        while (print_Node->next != NULL){
            printf(" %d", print_Node->key);
            print_Node = print_Node->next;
        }
    }
}

int main(){
    int M;
    int key;
    Node *arr;
    Node *free_Node, *real_free_Node;
    char input;
    scanf("%d", &M);
    arr = (Node *)malloc(sizeof(Node) * M);
    for (int i = 0; i < M; i++){
        arr[i].next = NULL;
    }
    while (1){
        scanf(" %c", &input);
        if (input == 'i'){
            scanf("%d", &key);
            insertItem(key, arr, M);
        }
        else if (input == 's'){
            printf("%d\n", findElement(key, arr, M));
        }
        else if (input == 'd'){
            printf("%d", deleteItem(key, arr, M));
        }
        else if (input == 'p'){
            print(arr, M);
        }
        else if (input == 'e'){
            break;
        }
    }
    /*for (int i = 0; i < M; i++){
        free_Node = arr[i].next;
        while (free_Node->next != NULL){
            real_free_Node = free_Node;
            free_Node = free_Node->next;
            free(real_free_Node);
        }
    }
    for (int i = 0; i < M; i++){
        free(arr);
    }*/
    return 0;
}