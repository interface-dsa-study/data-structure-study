#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int value;
    struct node *next;
}Node;
typedef struct list {
    int size;
    Node *head_node;
}List;
Node* create_node(int value) {
    Node *new_node=malloc(sizeof(*new_node));
    if (!new_node) {
        fprintf(stderr,"node malloc failed");
        exit(1);
    }
    new_node->value=value;
    new_node->next=NULL;
    return new_node;
}
List* create_list(int size, Node *head_node) {
    List *list=malloc(sizeof(*list));
    if (!list) {
        fprintf(stderr,"list malloc failed");
        exit(1);
    }
    list->size=size;
    list->head_node=head_node;
    return list;
}
Node* pop(List *list) {
    Node *target=list->head_node;
    list->head_node=list->head_node->next;
    list->size--;
    return target;
}
List* merge(List *list1,  List *list2) {
    List *sorted_list=create_list(0,NULL);
    if (!sorted_list) {
        fprintf(stderr,"list malloc failed");
        exit(1);
    }
    Node *sorted_list_pointer=NULL;
    sorted_list->size++;
    Node *temp=list1->head_node->value<list2->head_node->value?pop(list1):pop(list2);
    sorted_list->head_node=temp;
    sorted_list_pointer=sorted_list->head_node;
    while (list1->size&&list2->size) {
        sorted_list->size++;
        temp=list1->head_node->value<list2->head_node->value?pop(list1):pop(list2);
        sorted_list_pointer->next=temp;
        sorted_list_pointer=sorted_list_pointer->next;
        sorted_list_pointer->next=NULL;
    }
    if (list1->size){
        sorted_list->size+=list1->size;
        sorted_list_pointer->next=list1->head_node;
    }
    else {
        sorted_list->size+=list2->size;
        sorted_list_pointer->next=list2->head_node;
    }
    free(list1);
    free(list2);
    return sorted_list;
}
Node* move_time(Node *node, int times) {
    for (int i=0;i<times&&node->next;i++) node=node->next;
    return node;
}
List*  merge_sort(List *list) {
    if (list->size<=1) return list;
    List *list1=create_list(list->size/2,list->head_node);
    Node *list1_end=move_time(list->head_node,list1->size-1);
    List *list2=create_list(list->size-list1->size,list1_end->next);
    list1_end->next=NULL;
    list1=merge_sort(list1);
    list2=merge_sort(list2);
    list=merge(list1,list2);
    return list;
}
void free_node(Node *node) {
    if (node) {
        free_node(node->next);
        free(node);
    }
}
void print_list(List *list) {
    Node *pointer=list->head_node;
    while (pointer) {
        printf(" %d",pointer->value);
        pointer=pointer->next;
    }
}
int main() {
    setbuf(stdout,NULL);
    List *list=create_list(0,NULL);
    scanf("%d",&list->size);
    int value;
    scanf("%d",&value);
    list->head_node=create_node(value);
    Node *pointer=list->head_node;
    for (int i=1;i<list->size;i++) {
        scanf("%d",&value);
        pointer->next=create_node(value);
        pointer=pointer->next;
    }
    list=merge_sort(list);
    print_list(list);
    free_node(list->head_node);
    free(list);
    return 0;
}