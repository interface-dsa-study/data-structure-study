#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
    struct node *prev;
    int element;
    struct node *next;
}Node;
typedef struct deque {
    Node *front;
    Node *rear;
    int size;
}Deque;
void add_front(Deque *deque,int element) {
    Node *new_node=(Node*)malloc(sizeof(Node));
    if (new_node==NULL) {
        fprintf(stderr,"node malloc failed");
        exit(1);
    }
    new_node->prev=NULL;
    new_node->element=element;
    new_node->next=NULL;
    if (deque->size) {
        new_node->next=deque->front;
        deque->front->prev=new_node;
    }
    else {
        deque->rear=new_node;
    }
    deque->front=new_node;
    deque->size++;
}
void add_rear(Deque *deque,int element) {
    Node *new_node=(Node*)malloc(sizeof(Node));
    if (new_node==NULL) {
        fprintf(stderr,"node malloc failed");
        exit(1);
    }
    new_node->prev=NULL;
    new_node->element=element;
    new_node->next=NULL;
    if (deque->size) {
        new_node->prev=deque->rear;
        deque->rear->next=new_node;
    }
    else {
        deque->front=new_node;
    }
    deque->rear=new_node;
    deque->size++;
}
void delete_front(Deque *deque) {
    if (deque->size==0) {
        printf("underflow");
        exit(1);
    }
    Node *target=deque->front;
    if (deque->size>1) {
        deque->front=target->next;
        deque->front->prev=NULL;
    }
    else {
        deque->front=NULL;
        deque->rear=NULL;
    }
    free(target);
    deque->size--;
}
void delete_rear(Deque *deque) {
    if (deque->size==0) {
        printf("underflow");
        exit(1);
    }
    Node *target=deque->rear;
    if (deque->size>1) {
        deque->rear=target->prev;
        deque->rear->next=NULL;
    }
    else {
        deque->front=NULL;
        deque->rear=NULL;
    }
    free(target);
    deque->size--;
}
void print(Deque *deque) {
    Node *pointer=deque->front;
    while(pointer) {
        printf(" %d",pointer->element);
        pointer=pointer->next;
    }
    printf("\n");
}
void free_node(Node *node) {
    if (node) {
        free_node(node->next);
        free(node);
    }
}
int main() {
    setbuf(stdout,NULL);
    Deque deque;
    deque.front=NULL;
    deque.rear=NULL;
    deque.size=0;
    int calculate_time;
    scanf("%d",&calculate_time);
    for (int i=0;i<calculate_time;i++) {
        char input[3]={0};
        scanf("%s",input);
        if (strncmp(input,"AF",2)==0) {
            int element;
            scanf("%d",&element);
            add_front(&deque,element);
        }
        else if (strncmp(input,"AR",2)==0) {
            int element;
            scanf("%d",&element);
            add_rear(&deque,element);
        }
        else if (strncmp(input,"DF",2)==0) {
            delete_front(&deque);
        }
        else if (strncmp(input,"DR",2)==0) {
            delete_rear(&deque);
        }
        else if (strncmp(input,"P",1)==0) {
            print(&deque);
        }
    }
    free_node(deque.front);
}