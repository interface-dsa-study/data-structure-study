#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

typedef struct ListNode{
    int data;
    struct ListNode *prev;
    struct ListNode *next;
}ListNode;

void add_front(ListNode **pheader, ListNode **ptrailer, int data){
    ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->next = *pheader;
    new_node->prev = NULL;
    new_node->data = data;
    if (*pheader == NULL){
        *pheader = new_node;
        *ptrailer = new_node;
        return;
    }
    (*pheader)->prev = new_node;
    *pheader = new_node;
    //printf("%d %d\n", (*pheader)->data, (*ptrailer)->data);
    return;
}

void add_rear(ListNode **pheader, ListNode **ptrailer, int data){
    ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->prev = *ptrailer;
    new_node->next = NULL;
    new_node->data = data;
    if (*ptrailer == NULL){
        *pheader = new_node;
        *ptrailer = new_node;
        return;
    }
    (*ptrailer)->next = new_node;
    *ptrailer = new_node;
    return;
}

void delete_front(ListNode **pheader, ListNode **ptrailer){
    ListNode *removeNode = *pheader;
    *pheader = (*pheader)->next;
    if (*pheader == NULL){
        *ptrailer = NULL;
        free(removeNode);
        return;
    }
    //printf("%d %d\n", (*pheader)->data, (*ptrailer)->data);
    (*pheader)->prev = NULL;
    free(removeNode);
    return;
}

void delete_rear(ListNode **pheader, ListNode **ptrailer){
    ListNode *removeNode = *ptrailer;
    *ptrailer = (*ptrailer)->prev;
    if (*ptrailer == NULL){
        *pheader = NULL;
        free(removeNode);
        return;
    }
    (*ptrailer)->next = NULL;
    //printf("%d %d\n", (*pheader)->data, (*ptrailer)->data);
    free(removeNode);
    return;
}

void print(ListNode **pheader, ListNode **ptrailer){
    ListNode *printNode = *pheader;
    while (printNode != *ptrailer){
        printf(" %d", printNode->data);
        printNode = printNode->next;
    }
    printf(" %d", printNode->data);
    printf("\n");
    return;
}

int main(){
    ListNode *header = NULL;
    ListNode *trailer = NULL;
    int n;
    char tmp[3];
    int data;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf(" %s", tmp);
        if (strcmp("AF", tmp) == 0){
            scanf("%d", &data);
            add_front(&header, &trailer, data);
        }
        else if (strcmp("AR", tmp) == 0){
            scanf("%d", &data);
            add_rear(&header, &trailer, data);
        }
        else if (strcmp("DF", tmp) == 0){
            if (header == NULL){
                printf("underflow");
                break;
            }
            delete_front(&header, &trailer);
        }
        else if (strcmp("DR", tmp) == 0){
            if (trailer == NULL){
                printf("underflow");
                break;
            }
            delete_rear(&header, &trailer);
        }
        else if (strcmp("P", tmp) == 0){
            print(&header, &trailer);
        }
    }
    return 0;
}