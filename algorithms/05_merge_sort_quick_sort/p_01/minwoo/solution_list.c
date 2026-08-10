#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
}Node;

void make_list(Node** node, int num) {
    Node* newnode = malloc(sizeof(Node));
    newnode->next = NULL;
    newnode->data = num;
    if (*node == NULL) {
        *node = newnode;
    }
    else {
        Node* temp = *node;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newnode;
    }
}

Node* merge(Node* L1, Node* L2) {
    Node* L = NULL;
    Node* temp1 = NULL;
    Node* temp2 = NULL;
    while (L1 != NULL && L2 != NULL) {
        if (L1->data < L2->data) {
            temp1 = L1;
            L1 = L1->next;
        }
        else {
            temp1 = L2;
            L2 = L2->next;
        }
        if (L == NULL) {
            L = temp1;
            temp2 = L;
        }
        else {
            temp2->next = temp1;
            temp2 = temp2->next;
        }
    }
    if (L1 != NULL) {
        temp2->next = L1;
    }
    else {
        temp2->next = L2;
    }

    return L;
}

Node* partition(Node* node, int size) {
    Node* temp = node;
    for (int i = 1;i < size && temp->next != NULL; i++) {
        temp = temp->next;
    }
    Node* L2 = temp->next;
    temp->next = NULL;

    return L2;
}

Node* mergeSort(Node* node, int size) {
    if (size <= 1) {
        return node;
    }
    int k = size / 2; // 4 // 2 // 1
    Node* L2 = partition(node, k);
    Node* L1 = mergeSort(node, k);
    L2 = mergeSort(L2, size - k);
    Node* L = merge(L1, L2);

    return L;
}

void print(Node* list) {
    while (list) {
        printf(" %d", list->data);
        list = list->next;
    }
}

int main() {
    Node* List = NULL;
    int N, i, num;

    scanf("%d", &N);

    for (i = 0;i < N;i++) {
        scanf("%d", &num);
        make_list(&List, num);
    }

    List = mergeSort(List, N);

    print(List);

    return 0;
}