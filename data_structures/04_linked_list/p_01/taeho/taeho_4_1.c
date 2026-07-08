#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    struct node *prev;
    char element;
    struct node *next;
}Node;
typedef struct list {
    Node *head;
    Node *trailer;
    int size;
}List;
void initialize(List *list);
void add(List *list,int rank,char element);
void delete(List *list,int rank);
void get(List *list,int rank);
void print(List *list);
void free_list(Node *node);
int main() {
    List list;
    initialize(&list);
    int c_time;
    scanf("%d",&c_time);
    char input;
    int rank;
    char element;
    for (int i=0;i<c_time;i++) {
        scanf(" %c",&input);
        switch (input) {
            case 'A':
                scanf("%d %c",&rank,&element);
                add(&list,rank,element);
                break;
            case 'D':
                scanf("%d",&rank);
                delete(&list,rank);
                break;
            case 'G':
                scanf("%d",&rank);
                get(&list,rank);
                break;
            case 'P':
                print(&list);
                break;
        }
    }
    free_list(list.head);
    return 0;
}
void initialize(List *list) {
    list->head=(Node*)malloc(sizeof(Node));
    if (list->head==NULL) {
        fprintf(stderr,"header malloc failed");
        exit(-1);
    }
    list->trailer=(Node*)malloc(sizeof(Node));
    if (list->trailer==NULL) {
        fprintf(stderr,"header malloc failed");
        free(list->head);
        exit(-1);
    }
    list->head->prev=NULL;
    list->head->element='\0';
    list->head->next=list->trailer;
    list->trailer->prev=list->head;
    list->trailer->element='\0';
    list->trailer->next=NULL;
    list->size=0;
}
void add(List *list,int rank,char element) {
    if (rank<1||rank>list->size+1) {
        printf("invalid position\n");
        return;
    }
    Node *new_node=(Node*)malloc(sizeof(Node));
    if (new_node==NULL) {
        fprintf(stderr,"new node malloc failed");
        free_list(list->head);
        exit(-1);
    }
    new_node->element=element;
    Node *prev_node;
    Node *next_node;
    next_node=list->head;
    for (int i=0;i<rank;i++) {
        next_node=next_node->next;
    }
    prev_node=next_node->prev;
    prev_node->next=new_node;
    new_node->prev=prev_node;
    next_node->prev=new_node;
    new_node->next=next_node;
    list->size++;
}
void delete(List *list,int rank){
    if (rank<1||rank>list->size) {
        printf("invalid position\n");
        return;
    }
    Node *target_node;
    Node *prev_node;
    Node *next_node;
    target_node=list->head;
    for (int i=0;i<rank;i++) {
       target_node=target_node->next;
    }
    prev_node=target_node->prev;
    next_node=target_node->next;
    prev_node->next=next_node;
    next_node->prev=prev_node;
    free(target_node);
    list->size--;
}
void get(List *list,int rank) {
    if (rank<1||rank>list->size) {
        printf("invalid position\n");
        return;
    }
    Node *tmp=list->head->next;
    for (int i=1;i<rank;i++) {
        tmp=tmp->next;
    }
    printf("%c\n",tmp->element);
}
void print(List *list) {
    Node *tmp=list->head->next;
    for (int i=0;i<list->size;i++) {
        printf("%c",tmp->element);
        tmp=tmp->next;
    }
    printf("\n");
}
void free_list(Node *node) {
    if (node) {
        free_list(node->next);
        free(node);
    }
}