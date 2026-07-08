#include <stdio.h>
#include <stdlib.h>
typedef struct st{
    int price;
    struct st *next;
} StockSpanner;
typedef struct stack {
    StockSpanner *header_node;
    int size;
}stack;

StockSpanner* stockSpannerCreate(StockSpanner *top_node) {
    int value;
    scanf("%d",&value);
    StockSpanner *new_node=(StockSpanner*)malloc(sizeof(StockSpanner));
    if (new_node==NULL) {
        fprintf(stderr,"node malloc failed");
        exit(-1);
    }
    new_node->price=value;
    new_node->next=top_node;
    return new_node;
}

int stockSpannerNext(StockSpanner* obj, int price) {
    
}

void stockSpannerFree(StockSpanner* obj) {
    
}
int main(){
    stack s;
    s.size=0;
    s.header_node=(StockSpanner*)malloc(sizeof(StockSpanner));
    if (s.header_node==NULL) {
        fprintf(stderr,"malloc failed");
        exit(-1);
    }
    s.header_node->next=NULL;
    StockSpanner* top_node=s.header_node;
    for (;;){
        top_node=stockSpannerCreate(top_node);
    }

}