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
Node* create_node() {
    int value;
    scanf("%d",&value);

    return pointer->next;
}
int main() {
    List *list=malloc(sizeof(*list));
    if (!list) {
        fprintf(stderr,"list malloc failed");
        exit(1);
    }
    list->head_node=NULL;
    scanf("%d",&list->size);
    Node *pointer=list->head_node;
    for (int i=0;i<list->size;i++) pointer=create_node();

}