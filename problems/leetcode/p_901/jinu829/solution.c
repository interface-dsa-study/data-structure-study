#include<stdio.h>
#include<stdlib.h>

#define MAX_STACK_SIZE 10^4

typedef struct Stack{
    int price;
    int span;
}Stack;

typedef struct
{
    Stack stack[MAX_STACK_SIZE];
    int top_index;
} StockSpanner;

StockSpanner *stockSpannerCreate()
{
    StockSpanner *obj;
    obj = (StockSpanner *)malloc(sizeof(StockSpanner));

    if (obj == NULL){
        printf("StockSpanner did not defined!");
        return NULL;
    }
    obj->top_index = -1;
    return obj;
}

int stockSpannerNext(StockSpanner *obj, int price)
{ // 기간을 반환하는 함수
    int totalspan = 1;
    while (obj->top_index >= 0 && obj->stack[obj->top_index].price <= price){
        totalspan += obj->stack[obj->top_index].span;
        obj->top_index -= 1;
    }
    obj->top_index += 1;
    obj->stack[obj->top_index].price = price;
    obj->stack[obj->top_index].span = totalspan;

    return totalspan;
}

void stockSpannerFree(StockSpanner *obj)
{ // 공간 해제
    free(obj);
}

/**
 * Your StockSpanner struct will be instantiated and called as such:
 * StockSpanner* obj = stockSpannerCreate();
 * int param_1 = stockSpannerNext(obj, price);

 * stockSpannerFree(obj);
*/