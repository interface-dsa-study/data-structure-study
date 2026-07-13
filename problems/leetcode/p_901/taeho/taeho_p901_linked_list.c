#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int price;
    int span;
    struct Node *next;
}Node;
typedef struct {
    Node *top;
} StockSpanner;


StockSpanner* stockSpannerCreate() {
    StockSpanner *stack=(StockSpanner*)malloc(sizeof(StockSpanner));
    if (stack==NULL) {
        fprintf(stderr,"stack malloc failed");
        exit(-1);
    }
    stack->top=NULL;
    return stack;
}
Node * pop_node(Node *node) {
    Node *address=node->next;
    free(node);
    return address;
}
int stockSpannerNext(StockSpanner* obj, int price) {
    Node *new_node=(Node*)malloc(sizeof(Node));
    if (new_node==NULL) {
        fprintf(stderr,"node malloc failed");
        exit(-1);
    }
    new_node->price=price;
    new_node->span=1;
    while (obj->top&&obj->top->price<=price) {
        new_node->span+=obj->top->span;
        obj->top=pop_node(obj->top);
    }
    new_node->next=obj->top;
    obj->top=new_node;
    return new_node->span;
}
void free_node(Node *node) {
    if (node) {
        free_node(node->next);
        free(node);
    }
}
void stockSpannerFree(StockSpanner* obj) {
    free_node(obj->top);
    free(obj);
}